#include <iostream>
#include <vector>
#include <random>

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};


size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

struct data_grath
{
	int size;
	std::string sort;
	std::string type_vector;
	stats st;
};

/*
template <typename T>
stats bubble_sort(std::vector<T>& data);

template <typename T>
stats shaker_sort(std::vector<T>& data);
*/
template<typename T>
std::vector<T> create_random_vector(int size);
template<typename T>
void reverse_vector(std::vector<T>& vect);


template<typename T>
stats (*sort)(std::vector<T>& arr);

template <typename T>
void statistic(int size, std::vector<data_grath>& graph, stats sort(std::vector<T>& arr))
{
	data_grath info;
	stats average;
	stats st;
	std::vector<T> vect;
	for (int i = 0; i < 100; i++)
	{
		vect = create_random_vector<T>(size);
		st = sort(vect);
		average.comparison_count += st.comparison_count;
		average.copy_count += st.copy_count;
	}
	average.comparison_count /= 100;
	average.copy_count /= 100;
	
	info.size = size;
	info.st = average;
	info.type_vector = "average";
	info.sort = "bubble";
	
	graph.push_back(info);

	st = sort(vect);
	info.st = st;
	info.type_vector = "sorted";
	info.sort = "bubble";

	graph.push_back(info);

	reverse_vector(vect);
	st = sort(vect);
	info.st = st;
	info.type_vector = "reverse_sorted";
	info.sort = "bubble";

	graph.push_back(info);
}



template<typename T>
void reverse_vector(std::vector<T>& vect)
{
	for (int i = 0; i < vect.size() / 2; i++)
	{
		std::swap(vect[i], vect[vect.size() - 1 - i]);
	}
}


template<typename T>
std::vector<T> create_random_vector(int size)
{
	std::vector<T> data;
	int elem = 0;
	for (int i = 0; i < size; i++) {
		elem = -1000 + rand() + 2000;
		data.push_back(elem);
	}
	return data;
}

template <typename T>
stats bubble_sort(std::vector<T>& data)
{
	stats st;
	st.comparison_count = 0;
	st.copy_count = 0;
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
				st.copy_count++;
			}
			st.comparison_count++;
		}
	}
	return st;
}

template <typename T>
stats shaker_sort(std::vector<T>& data)
{
	stats st;
	st.comparison_count = 0;
	st.copy_count = 0;

	int right = data.size() - 1;
	int left = 0;
	while (left < right) {
		for (int i = left; i < right; i++) {
			if (data[i] > data[i + 1]) {
				std::swap(data[i], data[i + 1]);
				st.copy_count++;
			}
			st.comparison_count++;
		}
		right--;

		for(int i = right; i > left; i--) {
			if (data[i] < data[i - 1]) {
				std::swap(data[i], data[i - 1]);
				st.copy_count++;
			}
			st.comparison_count++;
		}
		left++;
	}
	return st;
}

int main() {
	std::vector<int> abc;
	for (int i = 10; i >= 4; i--)
	{
		abc.push_back(i);
	}
	
	/*
	for (int i = 0; i < abc.size(); i++)
	{
		std::cout << abc[i] << " ";
	}*/

	/*
	struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
	};
	*/
	auto vect = create_random_vector<int>(15);

	/*
	stats st = shaker_sort<int>(vect);

	reverse_vector<int>(vect);
	
	for (auto i = vect.begin(); i != vect.end(); i++)
	{
		std::cout << *i << " ";
	}
	*/
	std::vector<data_grath> graph;
	statistic<int>(100, graph, bubble_sort);
	int aboba = 0;
}