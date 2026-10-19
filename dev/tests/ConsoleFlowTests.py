#!/usr/bin/env python3
"""End-to-end REAPER console checks, including real process restart and EOF."""
import pathlib
import subprocess
import sys
import tempfile

APP = pathlib.Path(sys.argv[1])

def run(data_path, commands):
    result = subprocess.run([str(APP), str(data_path)], input=commands, text=True,
                            capture_output=True, timeout=8, check=True)
    return result.stdout + result.stderr

def require(value, output, scenario):
    if value not in output:
        raise AssertionError(f"{scenario}: expected {value!r}; output was:\n{output}")

with tempfile.TemporaryDirectory(prefix="reaper_week4_") as temp:
    path = pathlib.Path(temp) / "tasks.txt"
    first = run(path, "banana\n1\n  Build  REAPER  \n3\n1\nFinish tests\n1\n3\n2\n1\n1\n5\n")
    require("Enter a valid whole number.", first, "bad menu")
    require("Added task #1 with High priority.", first, "create high")
    require("Added task #2 with Low priority.", first, "create low")
    require("marked complete", first, "complete")
    require("Saved 2 task(s)", first, "save")
    assert path.is_file(), "save file not created"

    second = run(path, "2\n1\n1\nNext task\n2\n2\n1\n5\n")
    require("Loaded 2 task(s)", second, "restore")
    require("[X] #1 [High] -   Build  REAPER  ", second, "completion restored")
    require("[ ] #2 [Low] - Finish tests", second, "task restored")
    require("Added task #3 with Medium priority", second, "next ID")
    require("Saved 3 task(s)", second, "second save")

    original = path.read_bytes()
    path.write_text("REAPER_TASKS_V1\n1 3 0 \"first\"\n1 2 0 \"duplicate\"\n")
    corrupted = path.read_bytes()
    third = run(path, "1\nNew session task\n1\n5\n")
    require("Task file rejected", third, "corrupt data")
    require("will not be overwritten", third, "read-only protection")
    require("not saved", third, "no overwrite")
    assert path.read_bytes() == corrupted, "corrupt source was overwritten"

    path.write_bytes(original)
    eof = run(path, "")
    require("Input closed; ending REAPER session", eof, "EOF exits")
    require("Saved 3 task(s)", eof, "EOF saves")

    missing_dir_path = pathlib.Path(temp) / "absent_dir" / "tasks.txt"
    write_failure = run(missing_dir_path, "5\n")
    require("WARNING: Could not write the temporary task file.", write_failure, "save failure")

    path.write_text("NOT_A_REAPER_FILE\n")
    invalid_header = run(path, "5\n")
    require("invalid or uses an unsupported format", invalid_header, "invalid format")
    assert path.read_text() == "NOT_A_REAPER_FILE\n"

print("Week 4 console integration tests passed.")
