# coding: utf-8
# MIT License
#
# Copyright (c) 2018 Kalate Hexanome, 4IF, INSA Lyon
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

from tools.logger import logger
from tools.logger import trace
from tools import COMMANDS, PATHS, seconds_to_string, exec_
from tools import colored
from copy import copy
from time import time
import subprocess
import shlex
import os


def _return_code_to_str(code):
    codes = {
        # POSIX kill signals
        -1: 'SIGHUP',
        -2: 'SIGINT',
        -3: 'SIGQUIT',
        -4: 'SIGILL',
        -6: 'SIGABRT',
        -8: 'SIGFPE',
        -9: 'SIGKILL',
    }
    if code in codes:
        return codes[code]
    return str(code)


class Test:
    def __init__(self, name: str, full_path, should_fail: bool):
        self.name = name
        self.full_path = full_path
        self.should_fail = should_fail
        self.state = None
        self.succeeded = None

        self.display_name = '{} [{}]'.format(self.name, '-' if self.should_fail else '+')

    def execute(self):
        raise NotImplementedError


class GrammarTest(Test):
    @trace
    def execute(self, open_gui=False, open_gui_on_failure=False, show_stdout=False, show_stderr=False):
        start_time = time()
        grun_mode = '-gui' if open_gui else '-tree'
        command = shlex.split('{} Caramel r {} {}'.format(COMMANDS['grun'].format(
            build_grammar=PATHS['java-grammar']), grun_mode, self.full_path))
        logger.trace('Test command:', ' '.join(command))
        if len(self.full_path) == 0:  # Interactive test
            print('Enter grammar test input: (ended by ^D)')
        with subprocess.Popen(
                command,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
        ) as test_process:
            test_process.wait()

            # Get stdout and stderr
            out_str = list(map(lambda s: s.decode("utf-8"), test_process.stdout.readlines()))
            error_str = list(map(lambda s: s.decode("utf-8"), test_process.stderr.readlines()))

            # Save the test state
            self.state = {
                'stdout': sum(len(line.strip()) for line in out_str),
                'stderr': sum(len(line.strip()) for line in error_str),
                'time': time() - start_time
            }

            # Determine if unexpected errors, or successes, occurred
            errors = self.state['stderr'] > 0
            self.succeeded = errors if self.should_fail else not errors

            # Feed our user
            if self.succeeded:
                logger.info(
                    'Test {}'.format(self.display_name),
                    colored('succeeded.', color='green', attrs=['bold']),
                    colored('[%s]' % seconds_to_string(self.state['time']), color='yellow')
                )
            else:
                logger.info(
                    'Test {}'.format(self.display_name),
                    colored('failed.', color='red', attrs=['bold']),
                    colored('[%s]' % seconds_to_string(self.state['time']), color='yellow')
                )
                if open_gui_on_failure and not open_gui:
                    self.execute(open_gui=True, open_gui_on_failure=False)

            # Show stdout or stderr if asked
            if show_stdout or open_gui:
                if self.state['stdout'] == 0:
                    print(colored('No stdout output.', attrs=['bold']))
                else:
                    print('\n'.join([
                        '#' * 20,
                        colored('stdout output:', attrs=['bold']),
                        *out_str,
                        '-' * 20,
                    ]))
            if show_stderr or open_gui:
                if self.state['stderr'] == 0:
                    print(colored('No stderr output.', attrs=['bold']))
                else:
                    print('\n'.join([
                        '#' * 20,
                        colored('stderr output:', attrs=['bold']),
                        *error_str,
                        '-' * 20,
                    ]))


class SemanticTest(Test):
    @trace
    def execute(self, open_gui=False, open_gui_on_failure=False, show_stdout=False, show_stderr=False):
        start_time = time()

        command = './build/cpp-bin/Caramel --good-defaults {}'.format(self.full_path)
        logger.trace('Test command:', command)

        if len(self.full_path) == 0:  # Interactive test
            print('Enter grammar test input: (ended by ^D)')
        with subprocess.Popen(
                shlex.split(command),
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                env={'LD_LIBRARY_PATH': 'lib'}
        ) as test_process:
            test_process.wait()

            # Get stdout and stderr
            out_str = list(map(lambda s: s.decode("utf-8"), test_process.stdout.readlines()))
            error_str = list(map(lambda s: s.decode("utf-8"), test_process.stderr.readlines()))

            # Save the test state
            self.state = {
                'stdout': sum(len(line.strip()) for line in out_str),
                'stderr': sum(len(line.strip()) for line in error_str),
                'return_code': test_process.returncode,
                'time': time() - start_time
            }

            # Determine if unexpected errors, or successes, occurred
            errors = test_process.returncode != 0
            self.succeeded = errors if self.should_fail else not errors

            # Feed our user
            if self.succeeded:
                logger.info(
                    'Test {}'.format(self.display_name),
                    colored('succeeded.', color='green', attrs=['bold']),
                    colored('[%s]' % seconds_to_string(self.state['time']), color='yellow')
                )
            else:
                logger.info(
                    'Test {}'.format(self.display_name),
                    colored('failed #{}.'.format(_return_code_to_str(test_process.returncode)),
                            color='red', attrs=['bold']),
                    colored('[%s]' % seconds_to_string(self.state['time']), color='yellow')
                )
                if open_gui_on_failure and not open_gui:
                    self.execute(open_gui=True, open_gui_on_failure=False)

            # Show stdout or stderr if asked
            if show_stdout or open_gui:
                if self.state['stdout'] == 0:
                    print(colored('No stdout output.', attrs=['bold']))
                else:
                    print('\n'.join([
                        '#' * 20,
                        colored('stdout output:', attrs=['bold']),
                        ''.join(out_str),
                        '-' * 20,
                    ]))
            if show_stderr or open_gui:
                if self.state['stderr'] == 0:
                    print(colored('No stderr output.', attrs=['bold']))
                else:
                    print('\n'.join([
                        '#' * 20,
                        colored('stderr output:', attrs=['bold']),
                        ''.join(error_str),
                        '-' * 20,
                    ]))


class BackendTest(Test):
    @trace
    def execute(self, open_gui=False, open_gui_on_failure=False, show_stdout=False, show_stderr=False):
        start_time = time()

        command = './build/cpp-bin/Caramel --good-defaults {}'.format(self.full_path)
        logger.trace('Test command:', command)

        if len(self.full_path) == 0:  # Interactive test
            print('Enter grammar test input: (ended by ^D)')
        with subprocess.Popen(
                shlex.split(command),
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                env={'LD_LIBRARY_PATH': 'lib'}
        ) as test_process:
            test_process.wait()

            # Get stdout and stderr
            out_str = list(map(lambda s: s.decode("utf-8"), test_process.stdout.readlines()))
            error_str = list(map(lambda s: s.decode("utf-8"), test_process.stderr.readlines()))

            # Save the test state
            self.state = {
                'stdout': sum(len(line.strip()) for line in out_str),
                'stderr': sum(len(line.strip()) for line in error_str),
                'return_code': test_process.returncode,
                'time': time() - start_time
            }

            # Determine if unexpected errors, or successes, occurred
            errors = test_process.returncode != 0
            self.succeeded = errors if self.should_fail else not errors

            # Feed our user
            if self.succeeded:
                logger.info(
                    'Test {}'.format(self.display_name),
                    colored('succeeded.', color='green', attrs=['bold']),
                    colored('[%s]' % seconds_to_string(self.state['time']), color='yellow')
                )
            else:
                logger.info(
                    'Test {}'.format(self.display_name),
                    colored('failed #{}.'.format(_return_code_to_str(test_process.returncode)),
                            color='red', attrs=['bold']),
                    colored('[%s]' % seconds_to_string(self.state['time']), color='yellow')
                )
                if open_gui_on_failure and not open_gui:
                    self.execute(open_gui=True, open_gui_on_failure=False)

            # Show stdout or stderr if asked
            if show_stdout or open_gui:
                if self.state['stdout'] == 0:
                    print(colored('No stdout output.', attrs=['bold']))
                else:
                    print('\n'.join([
                        '#' * 20,
                        colored('stdout output:', attrs=['bold']),
                        ''.join(out_str),
                        '-' * 20,
                    ]))
            if show_stderr or open_gui:
                if self.state['stderr'] == 0:
                    print(colored('No stderr output.', attrs=['bold']))
                else:
                    print('\n'.join([
                        '#' * 20,
                        colored('stderr output:', attrs=['bold']),
                        ''.join(error_str),
                        '-' * 20,
                    ]))


class Tests:
    def __init__(self):
        self.tests = []
        pass

    @trace
    def check_build(self):
        if not os.path.isdir('build'):
            logger.critical(colored(' '.join([
                'The build directory is absent! Try to build before',
                'running tests, or to add --build to the command.'
            ]), color='red'))
            exit(1)

    @trace
    def add_test(self, name: str, full_path, should_fail: bool):
        raise NotImplementedError

    @trace
    def discover(self, base_directory, only=None):
        # Check if there are tests
        if not os.path.isdir(base_directory):
            logger.critical('The {} directory is absent!'.format(base_directory))
            exit(1)

        if only is not None and isinstance(only, list):
            only = set(only)

        # Discover the tests
        nb_tests_before = len(self.tests)
        for test_directory in ['.', *sorted(os.listdir(base_directory))]:
            logger.debug('Looking for tests in:', test_directory)
            if os.path.isdir(os.path.join(base_directory, test_directory)):
                for test_file in sorted(os.listdir(os.path.join(base_directory, test_directory))):
                    if only is None or test_file in only:
                        if only is not None:
                            only.remove(test_file)
                        test_path = os.path.join(base_directory, test_directory, test_file)
                        if os.path.isfile(test_path):
                            self.add_test(test_file, test_path, test_directory == 'invalid')

        # Consider remaining test files as relative paths
        if only is not None:
            for test_path in only:
                if not os.path.isfile(test_path):
                    logger.fatal('Could not find test: {}'.format(test_path))
                    exit(1)
                self.add_test(test_path.split('/')[-1], test_path, False)

        logger.info('Discovered', colored(
            '{} tests.'.format(len(self.tests) - nb_tests_before), color='yellow'))

    @trace
    def run_all(self, *args, **kwargs):
        self.check_build()
        for test in self.tests:
            test.execute(*args, **kwargs)


class GrammarTests(Tests):
    def __init__(self):
        super().__init__()

    @trace
    def add_test(self, name: str, full_path, should_fail: bool):
        self.tests.append(GrammarTest(name, full_path, should_fail))
        logger.debug('Added grammar test {}.'.format(name))


class SemanticTests(Tests):
    def __init__(self):
        super().__init__()

    @trace
    def add_test(self, name: str, full_path, should_fail: bool):
        self.tests.append(SemanticTest(name, full_path, should_fail))
        logger.debug('Added semantic test {}.'.format(name))


class BackendTests(Tests):
    def __init__(self):
        super().__init__()

    @trace
    def add_test(self, name: str, full_path, should_fail: bool):
        self.tests.append(BackendTest(name, full_path, should_fail))
        logger.debug('Added back-end test {}.'.format(name))


@trace
def test_grammar(args):
    logger.info('Running grammar tests...')

    if args.build:
        from tools.build import build_grammar
        build_grammar(args)

    if args.interactive and len(args.test_files) > 0:
        logger.warn('Running in interactive mode, ignoring test files.')
        args.test_files = []

    if args.all:
        args.test_files = None

    # Run the tests
    grammar_tests = GrammarTests()
    grammar_tests.check_build()
    if args.interactive:
        grammar_tests.add_test('interactive test', '', False)
    else:
        grammar_tests.discover(PATHS['grammar-test-dir'], only=args.test_files)
    grammar_tests.run_all(
        open_gui=args.gui,
        open_gui_on_failure=args.gui_on_failure,
        show_stdout=args.stdout,
        show_stderr=args.stderr,
    )


@trace
def test_semantic(args):
    logger.info('Running semantic tests...')

    if args.build:
        from tools.build import build_grammar, build_caramel
        build_grammar(args)
        build_caramel(args)

    if args.interactive and len(args.test_files) > 0:
        logger.warn('Running in interactive mode, ignoring test files.')
        args.test_files = []

    if args.all:
        args.test_files = None

    # Run the tests
    semantic_tests = SemanticTests()
    if args.interactive:
        semantic_tests.add_test('interactive test', '', False)
    else:
        semantic_tests.discover(PATHS['semantic-test-dir'], only=args.test_files)
    semantic_tests.run_all(
        open_gui=args.gui,
        open_gui_on_failure=args.gui_on_failure,
        show_stdout=args.stdout,
        show_stderr=args.stderr,
    )


@trace
def test_backend(args):
    # TODO: Refactor => factorize semantic and back-end?

    logger.info('Running back-end tests...')

    if args.build:
        from tools.build import build_grammar, build_caramel
        build_grammar(args)
        build_caramel(args)

    if args.interactive and len(args.test_files) > 0:
        logger.warn('Running in interactive mode, ignoring test files.')
        args.test_files = []

    if args.all:
        args.test_files = None

    # Run the tests
    backend_tests = BackendTests()
    if args.interactive:
        backend_tests.add_test('interactive test', '', False)
    else:
        backend_tests.discover(PATHS['backend-test-dir'], only=args.test_files)
    backend_tests.run_all(
        open_gui=args.gui,
        open_gui_on_failure=args.gui_on_failure,
        show_stdout=args.stdout,
        show_stderr=args.stderr,
    )


@trace
def test_programs(args):
    logger.warn('Programs tests not implemented :(')


@trace
def test_all(args):
    logger.info('Running all tests...')

    # Execute grammar tests
    grammar_args = copy(args)
    grammar_args.all = True
    grammar_args.gui = False
    grammar_args.gui_on_failure = False
    test_grammar(grammar_args)

    # Execute semantic tests
    semantic_args = copy(args)
    semantic_args.all = True
    semantic_args.gui = False
    semantic_args.gui_on_failure = False
    test_semantic(semantic_args)

    # Execute back-end tests
    backend_args = copy(args)
    backend_args.all = True
    backend_args.gui = False
    backend_args.gui_on_failure = False
    test_backend(backend_args)

    # Execute programs tests
    programs_args = copy(args)
    programs_args.all = True
    programs_args.gui = False
    programs_args.gui_on_failure = False
    test_programs(programs_args)
