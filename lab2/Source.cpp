#include <iostream>
#include <vector>
#include <random>

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};


//size_t lcg() {
//	static size_t x = 0;
//	x = (1021 * x + 24631) % 116640;
//	return x;
//}

//struct data_grath
//{
//	int size;
//	std::string sort;
//	std::string type_vector;
//	stats st;
//};

/*
template <typename T>
stats bubble_sort(std::vector<T>& data);

template <typename T>
stats shaker_sort(std::vector<T>& data);
*/
//template<typename T>
//std::vector<T> create_random_vector(int size);
//template<typename T>
//void reverse_vector(std::vector<T>& vect);


template<typename T>
stats (*sort)(std::vector<T>& data);

//template <typename T>
//void statistic(int size, std::vector<data_grath>& graph, stats sort(std::vector<T>& arr))
//{
//	data_grath info;
//	stats average;
//	stats st;
//	std::vector<T> vect;
//	for (int i = 0; i < 100; i++)
//	{
//		vect = create_random_vector<T>(size);
//		st = sort(vect);
//		average.comparison_count += st.comparison_count;
//		average.copy_count += st.copy_count;
//	}
//	average.comparison_count /= 100;
//	average.copy_count /= 100;
//	
//	info.size = size;
//	info.st = average;
//	info.type_vector = "average";
//	info.sort = "bubble";
//	
//	graph.push_back(info);
//
//	st = sort(vect);
//	info.st = st;
//	info.type_vector = "sorted";
//	info.sort = "bubble";
//
//	graph.push_back(info);
//
//	reverse_vector(vect);
//	st = sort(vect);
//	info.st = st;
//	info.type_vector = "reverse_sorted";
//	info.sort = "bubble";
//
//	graph.push_back(info);
//}



template<typename T>
std::vector<T> reverse_vector(std::vector<T> data) {
	for (int i = 0; i < data.size() / 2; i++) {
		std::swap(data[i], data[data.size() - 1 - i]);
	}
	return data;
}


template<typename T>
std::vector<T> create_random_vector(int n, int min, int max)
{
	std::vector<T> data;
	int elem;
	srand(time(0));
	for (int i = 0; i < n; i++) {
		elem = -rand() % min + rand() % max;
		data.push_back(elem);
	}
	return data;
}

//std::vector<T> create_random_vector(int size)
//{
//	std::vector<T> data;
//	int elem = 0;
//	for (int i = 0; i < size; i++) {
//		elem = -1000 + rand() + 2000;
//		data.push_back(elem);
//	}
//	return data;
//}

template <typename T>
stats bubble_sort(std::vector<T>& data)
{
	/*stats st;*/
	stats info;
	for(int i = 1; i < data.size(); i++)
	{
		for(int j = 0; j < data.size()-i; j++ )
		{
			if (data[j] > data[j+1]){
				/*
				int temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;*/
				std::swap(data[j], data[j + 1]);
				info.copy_count++;
			}
			info.comparison_count++;
		}
	}
	return info;
}

template <typename T>
stats shaker_sort(std::vector<T>& data)
{
	stats info;

	int right = data.size() - 1;
	int left = 0;
	while (left < right) {
		for (int i = left; i < right; i++) {
			if (data[i] > data[i + 1]) {
				std::swap(data[i], data[i + 1]);
				info.copy_count++;
			}
			info.comparison_count++;
		}
		right--;

		for(int i = right; i > left; i--) {
			if (data[i] < data[i - 1]) {
				std::swap(data[i], data[i - 1]);
				info.copy_count++;
			}
			info.comparison_count++;
		}
		left++;
	}
	return info;
}

template <typename T>
stats comb_sort(std::vector<T>& data)
{
	stats info;
	double factor = 1.247;
	int len = data.size();
	int gap = len;
	while (gap > 1) {
		gap = int(gap / factor);
		if (gap < 1) { gap = 1; }
		info.comparison_count++;
		int i = 0;
		while (gap + i < len)
		{
			if (data[i] > data[i + gap]) {
				std::swap(data[i], data[i + gap]);
				info.copy_count++;
			}
			i++;
			info.comparison_count++;

		}

	}
	for (int i = 1; i < len; i++) {
		int j = i;
		while (j>0 && data[j-1]>data[j])
		{
			std::swap(data[j-1], data[j]);
			j--;
			info.copy_count++;
		}
		info.comparison_count++;
	}
	return info;
}

template <typename T>
std::vector<stats> generate_stats(int len, stats sort(std::vector<T>& data))
{
	std::vector<stats> arr;

	// а. в среднем (генерация 100 массивов)
	stats info_rand;
	for (int i = 0; i < 100; i++)
	{
		auto vect = create_random_vector<int>(len, -10000, 10000);
		stats st_rand = sort(vect);
		info_rand.comparison_count += st_rand.comparison_count;
		info_rand.copy_count += st_rand.copy_count;
	}
	info_rand.comparison_count /= 100;
	info_rand.copy_count /= 100;
	arr.push_back(info_rand);
	std::cout << "Average comparison " << len << " : " << info_rand.comparison_count << std::endl;
	std::cout << "Average copy " << len << " : " << info_rand.copy_count << std::endl;
	std::cout << std::endl;

	// б. для отсортированного массива
	auto sort_vec = create_random_vector<int>(len, -10000, 10000);
	sort(sort_vec);
	stats info_sort = sort(sort_vec);
	arr.push_back(info_sort);
	std::cout << "Sort comparison " << len << " : " << info_sort.comparison_count << std::endl;
	std::cout << "Sort copy " << len << " : " << info_sort.copy_count << std::endl;
	std::cout << std::endl;

	// в. для обратно отсортированного массива
	auto reverse_vec = reverse_vector(sort_vec);
	auto info_rev = sort(reverse_vec);
	arr.push_back(info_rev);
	std::cout << "Reverse comparison " << len << " : " << info_rev.comparison_count << std::endl;
	std::cout << "Reverse copy " << len << " : " << info_rev.copy_count << std::endl;
	std::cout << std::endl;

	return arr;
}

//template <typename T>
void statistic_sort(stats sort(std::vector<int>& data)) {
	for (int i = 1000; i < 10001; i += 1000) {
		generate_stats(i, sort);
	}
	for (int i = 25000; i < 50001; i += 25000) {
		generate_stats(i, sort);
	}
	for (int i = 50000; i < 100001; i += 50000) {
		generate_stats(i, sort);
	}
}
//
//template <typename T>
void all_info()
{
	std::cout << "SHAKER SORT" << std::endl;
	statistic_sort(shaker_sort);
	std::cout << "BUBBLE SORT" << std::endl;
	statistic_sort(bubble_sort);
	std::cout << "COMB SORT" << std::endl;
	statistic_sort(comb_sort);
}


int main() {
	all_info();
	/*std::vector<int> abc;
	for (int i = 10; i >= 4; i--)
	{
		abc.push_back(i);
	}

	stats st = comb_sort<int>(abc);

	
	for (int i = 0; i < abc.size(); i++)
	{
		std::cout << abc[i] << " ";
	}
	*/

	/*
	struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
	};
	*/
	/*auto vect = create_random_vector<int>(15);*/

	/*
	stats st = shaker_sort<int>(vect);

	reverse_vector<int>(vect);
	
	for (auto i = vect.begin(); i != vect.end(); i++)
	{
		std::cout << *i << " ";
	}
	*/
	/*std::vector<data_grath> graph;
	statistic<int>(100, graph, bubble_sort);
	int aboba = 0;*/
}