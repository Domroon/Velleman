#!/usr/bin/python3
from ctypes import *

libc = cdll.LoadLibrary("")
printf = libc.printf
printf(b"hello world\n")


def main():
    print("Hello World")


if __name__ == '__main__':
    main()