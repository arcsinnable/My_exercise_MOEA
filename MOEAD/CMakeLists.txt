cmake_minimum_required(VERSION 3.16)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp global.h global.cpp test_problem.cpp test_problem.h memory.cpp memory.h initialize.cpp initialize.h population.cpp population.h random.cpp random.h metaheuritics.cpp metaheuritics.h evaluation.cpp evaluation.h print.cpp print.h crossover.cpp crossover.h mutation.cpp mutation.h dominance_relation.cpp dominance_relation.h diversity_metric.cpp diversity_metric.h utility.cpp utility.h)