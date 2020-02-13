// Copyright 2017 Coman Diana Stefania
#pragma once

#ifndef SORT_H
#define SORT_H

#include <vector>
#include <functional>

using std::vector;

template <typename TObject>
void MergeSort(vector<TObject>* array,
				int begin, int end,
				std::function<bool(const TObject& left,
								  const TObject& right)> compare);

template <typename TObject>
void Merge(vector<TObject>* array, int begin, int mid, int end,
		   std::function<bool(const TObject& left,
							  const TObject& right)> compare);

#endif  // SORT_H
