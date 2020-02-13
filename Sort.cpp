// Copyright 2017 Coman Diana Stefania
#include "Sort.h"
#include "Player.h"
#include "FireExchange.h"

#include <algorithm>
#include <vector>
#include <functional>

using std::vector;

template <typename TObject>
void Merge(vector<TObject>* array, int begin, int mid, int end,
		   std::function<bool(const TObject& left,
							  const TObject& right)> compare) {
	int size1 = mid - begin + 1;
	int size2 = end - mid;

	vector<TObject> l(size1);
	vector<TObject> r(size2);

	for (int i = 0; i < size1; i++) {
		l[i] = (*array)[begin + i];
	}
	for (int i = 0; i < size2; i++) {
		r[i] = (*array)[mid + i + 1];
	}

	int i = 0;
	int j = 0;
	int pos = begin;
	while (i < size1 && j < size2) {
		if (compare(l[i], r[j])) {
			(*array)[pos] = l[i++];
		} else {
			(*array)[pos] = r[j++];
		}
		pos++;
	}

	while (i < size1) {
		(*array)[pos] = l[i++];
		pos++;
	}

	while (j < size2) {
		(*array)[pos] = r[j++];
		pos++;
	}
}

template <typename TObject>
void MergeSort(vector<TObject>* array,
			   int begin, int end,
			   std::function<bool(const TObject& left,
								  const TObject& right)> compare) {
	if (begin < end) {
		int mid = begin + (end - begin) / 2;

		MergeSort(array, begin, mid, compare);
		MergeSort(array, mid + 1, end, compare);

		Merge(array, begin, mid, end, compare);
	}
}

template void MergeSort(vector<Player>* array,
						int begin, int end,
						std::function<bool(const Player& left,
										   const Player& right)> compare);
template void MergeSort(vector<FireExchange>* array,
						int begin, int end,
						std::function<bool(const FireExchange& left,
										  const FireExchange& right)> compare);
