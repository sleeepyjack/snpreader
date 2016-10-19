/*
 * Macros.h
 *
 *  Created on: 16/12/2014
 *      Author: jorge
 */

#ifndef MACROS_H_
#define MACROS_H_

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <assert.h>
#include <limits.h>
#include <zlib.h>
#include <math.h>
#include <pthread.h>
#include <iterator>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

using namespace std;

// For reading the SNP
#define SNP_MAX_NAME_SIZE 128

// For initial size of the arrays
#define DEFAULT_NUM_INDS 1024
#define DEFAULT_NUM_SNPS 524288

// Genotype encoding
#define GENO_AA	0
#define GENO_Aa	1
#define GENO_aa	2

// Output
//#define DEBUG // To print the logs of debugging

#endif /* MACROS_H_ */
