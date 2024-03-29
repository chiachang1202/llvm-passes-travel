//=============================================================================
// FILE:
//      input_for_mba_sub.c
//
// DESCRIPTION:
//      Sample input file for the MBASub pass.
//
// License: MIT
//=============================================================================
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int a = atoi(argv[1]), b = atoi(argv[2]), c = atoi(argv[3]),
      d = atoi(argv[4]);
  float g = 1.3, h = 2.4;
  double j = 3.9, k = 0.4;

  int e = a - b;
  int f = c - d;
  float i = g - h;
  double l = j - k;

  return e - f;
}