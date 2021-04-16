#! /usr/bin/python3.6
# -*- coding: utf-8 -*-

# Brandon Esquivel Molina
# B52571
# IE724 Laboratorio de programacion y microcontroladores
# EIE, UCR
# Lab 1: N numeros primos
# Ubuntu 18.04
# python 3.6.9 64b

# cmd to run: python laboratorio1.py <N>
# where N is a integer > 1
# the program starts at 2, the number 1 is not set as prime

# IMPORTS
import sys

# DEFINES
first_prime = 2

# DEF FUNCTIONS
def seraPrimo(N):
    if N < 1:                       # error case
        return False
    else:
        for j in range(first_prime, N):     # iterative form using residue analysis, including N
            if N % j == 0:          # condition to non-prime
                return False
        return True

# DEF MAIN PROGRAM
def main():
    N = int(sys.argv[1])
    if N < first_prime:
        print("\nPlease Select N>1.\n")
    for i in range(first_prime, N+1):
        answer = seraPrimo(i)
        if answer is True:
            print(i)

if __name__ == '__main__':
    main()
