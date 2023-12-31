#include <iostream>
#include <random>
#include <ranges>
#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>
#include <chrono>
 
using namespace std;
using namespace std::chrono;
 
float median_nth_element(const std::vector<float>& d){
	vector<float> vf = d;
	std::nth_element(vf.begin(), vf.begin()+ vf.size()/2, vf.end());
	return vf[(vf.size()-1)/2];
}
 
// Floating point version, maps int to ordered floats 
float to_float(uint32_t n){
    n += ((1<<23)-1);
    if(n & (1<<31))
        n ^= (1<<31);
    else
        n=~n;
    return std::bit_cast<float>(n);
}

constexpr uint32_t plus_inf = ~((1<<23)-1) - ((1<<23)-1);

float median2(const std::vector<float>& d){
	auto indices = std::views::iota(0u, plus_inf+1);

	auto counts = indices | std::views::transform([&](uint32_t partition){
		return std::ranges::count_if(d, [&](float i){
			return i<=to_float(partition);}
		);
	});

	auto b = std::ranges::lower_bound(counts, (d.size()+1)/2);

	return to_float(b - counts.begin());
}
 


int main(){
    mt19937 rng;
    vector<float> d;
 
    for(int i=0; i < 100'000'000; i++)
        d.push_back(exponential_distribution<>()(rng));   
	
	
	auto start = steady_clock::now();

	start = steady_clock::now();
    cout << median_nth_element(d) << " " << duration_cast<milliseconds>(steady_clock::now()-start).count() << "ms\n";

	start = chrono::steady_clock::now();
    cout << median2(d) << " " << duration_cast<milliseconds>(steady_clock::now()-start).count() << "ms\n";
 
}

