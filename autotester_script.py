import argparse
import os
import subprocess
import sys
import xml.etree.ElementTree
from typing import List

SOURCE_SUFFIX = "_source.txt"
QUERY_SUFFIX = "_queries.txt"
OUTPUT_SUFFIX = ".xml"
total_queries = 0
total_passes = 0


class bcolors:
    HEADER = '\033[95m'
    END = '\033[96m'
    OKGREEN = '\033[92m'
    FAIL = '\033[91m'


class TestCase:
    def __init__(self, name: str, source: str, query: str, output: str):
        self.name = name
        self.source = source
        self.query = query
        self.output = output


def get_test_paths(testDir: str, outputDir: str) -> List[TestCase]:
    testcases = []
    sorted_files = sorted(os.listdir(testDir))
    for file in sorted_files:
        # To get the starting file (Source -> Query)
        if file.endswith(SOURCE_SUFFIX):
            test_name = file[:-len(SOURCE_SUFFIX)]
            source_path = os.path.join(testDir, f'{test_name}{SOURCE_SUFFIX}').replace('\\', '/')
            query_path = os.path.join(testDir, f'{test_name}{QUERY_SUFFIX}').replace('\\', '/')
            output_path = os.path.join(outputDir, f'{test_name}{OUTPUT_SUFFIX}').replace('\\', '/')
            curr_test = TestCase(test_name, source_path, query_path, output_path)
            testcases.append(curr_test)
    return testcases


def print_out_xml_results(testcase: TestCase):
    global total_passes
    global total_queries
    no_of_queries = 0
    no_of_passes = 0
    msg = ''
    root_node = xml.etree.ElementTree.parse(testcase.output).getroot()
    print(bcolors.HEADER + f'<<<<<<<<<<<<<<< Test result for {testcase.name} >>>>>>>>>>>>>>>')

    for test_query in root_node.iter('query'):
        no_of_queries += 1
        total_queries += 1
        # Get test query's details
        query_id = test_query.find('id')
        comment = query_id.attrib.get('comment')

        if test_query.find('passed') is not None:
            no_of_passes += 1
            total_passes += 1
            msg = 'SUCCESS'
            time_taken = test_query.find('time_taken').text
            print(bcolors.OKGREEN + f'{msg} - {query_id}: {comment} passed ({time_taken})')
        else:
            if test_query.find('exception') is not None:
                msg = 'EXCEPTION'
            elif test_query.find('failed') is not None:
                msg = 'FAILED'
            elif test_query.find('crash') is not None:
                msg = 'CRASH'
            else:
                msg = 'TIMEOUT'
            print(bcolors.FAIL + f'{msg} - {query_id}: {comment} failed')
    print(
        bcolors.END + f'{testcase.name}: {no_of_passes} passed, {no_of_queries - no_of_passes} failed, {no_of_queries} total')


def main():
    global total_passes
    global total_queries

    # Reading input paths from cmd line
    parser = argparse.ArgumentParser()
    parser.add_argument('autotester_exe')
    parser.add_argument('test_files_dir')
    args = parser.parse_args()

    # Normalize paths
    autotester_exe = os.path.normpath(args.autotester_exe)
    test_files_dir = os.path.normpath(args.test_files_dir)
    output_dir = os.path.join(test_files_dir, 'output')
    os.makedirs(output_dir, exist_ok=True)

    # Get the respective query, source and out paths
    tests = get_test_paths(test_files_dir, output_dir)

    # Iterate through each test case
    for testcase in tests:
        print(f'Running test cases for {testcase.name}', flush=True)
        subprocess.run([
            autotester_exe,
            testcase.source,
            testcase.query,
            testcase.output
        ], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        print_out_xml_results(testcase)

    if total_queries == total_passes:
        print(bcolors.OKGREEN + f'Passed: {total_passes} Failed: {total_queries - total_passes}')
        sys.exit(0)
    else:
        print(bcolors.FAIL + f'Passed: {total_passes} Failed: {total_queries - total_passes}')
        sys.exit(1)


if __name__ == '__main__':
    main()
