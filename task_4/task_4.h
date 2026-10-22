
#include "Kmer.h"
#include "subtask4_1.h"
#include "subtask4_2.h"
#include "subtask4_3.h"
#include "subtask4_4.h"

// TODO
// find adapter
// strip adapter (new file)
// length distribution of stripped adapter file
// deduplicate
// frequency distribution of deduplicated
// common suffix in stripped deduplicated

// TOREAD
// Adapter
// Length distribution after stripping
// Frequency distribution after stripping, then deduplicate
// common

//https://academic.oup.com/bioinformaticsadvances/article/3/1/vbac085/6835406
void task_4() {

	// Find adapter
	// READS: main set
	// PRINTS: adapter
	subtaks4_1(
	"dna_files/tdt4287-unknown-adapter.txt"
	);

	// Remove adapter, write file, print length distribution
	// READS: main set, WRITES: stripped adapter
	// PRINTS: length distribution
	subtask4_2(
	"AGATCGGAAGAGCACACGTCTGAACTCCAGTCACGTAGAGATCTCGTATGCCGTCTTCTGCTTGAA",
	"dna_files/tdt4287-unknown-adapter.txt",
	"dna_files/task4/stripped_adapter.txt"
	);


	// Reads stripped and writes deduplicated, prints frequency distribution
	// READS: stripped adapter, WRITES: deduplicated stripped adapter
	// PRINTS: frequency distribution
	subtask4_3(
	"dna_files/task4/stripped_adapter.txt",
	"dna_files/task4/deduplicated_stripped_adapter.txt"
	);


	// Check unique sequence set, any common suffix?
	// READS: deduplicated stripped adapter
	// PRINTS: adapter
	subtask4_4(
	"dna_files/task4/deduplicated_stripped_adapter.txt"
	); // AAACCGTTACCATTACTGAGT
}