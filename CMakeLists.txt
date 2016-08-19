cmake_minimum_required(VERSION 3.6)
project(ShittyTextSearch)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SparseVector.cpp SparseVector.h content_stream.h content_stream.cpp TokenVectorCreator.cpp TokenVectorCreator.h TokenModifier.h StopWordRemover.cpp StopWordRemover.h TokenCaseConverter.cpp TokenCaseConverter.h TextProcessor.cpp TextProcessor.h SnippetGenerator.cpp SnippetGenerator.h IndexedDocument.cpp IndexedDocument.h DocumentRepository.cpp DocumentRepository.h ContentLoader.cpp ContentLoader.h DocumentRanker.cpp DocumentRanker.h)
find_package(Boost COMPONENTS filesystem thread REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(ShittyTextSearch ${SOURCE_FILES})
    target_link_libraries(ShittyTextSearch ${Boost_LIBRARIES})
endif()
