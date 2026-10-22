cmake_minimum_required(VERSION 4.3)
project(very_fast_and_cool_DNA_sequencer_for_sequencing_DNA)

set(CMAKE_CXX_STANDARD 23)

add_executable(very_fast_and_cool_DNA_sequencer_for_sequencing_DNA main.cpp
        task_1/KPM_matcher.cpp
        task_5/task_5.h
        task_4/Kmer.cpp
        task_4/Kmer.h
        task_2/Edit_diastance.cpp
        task_4/subtask4_1.h
        task_4/subtask4_1.h
        task_4/subtask4_2.h
        task_4/subtask4_3.h
        task_4/subtask4_4.h
        task_4/subtask4_4.h
        task_4/subtask4_4.h
        task_4/has_3_adapter_edit.h
        task_4/remove_lines_with_adapter.h
        task_4/count_adapter_occurrence.h
)
