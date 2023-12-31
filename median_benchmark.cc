#include <iostream>
#include <random>
#include <ranges>
#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>
#include <chrono>
#include <cassert> 
 
using namespace std;
using namespace std::chrono;
using namespace std::literals;

constexpr uint32_t median_uint(const std::vector<uint32_t>& d){
	auto indices = views::iota(0u, ~0u);
	auto counts = indices | views::transform([&](uint32_t partition){
		return ranges::count_if(d, [&](auto i){
			return i <= partition;
		});
	});

	auto b = ranges::lower_bound(counts, (1+d.size())/2);
	return b-counts.begin();
}

constexpr uint32_t median_uint2(const std::vector<uint32_t>& d){
	auto [low, high] = ranges::minmax(d);
	auto indices = views::iota(low, high);
	auto counts = indices | views::transform([&](uint32_t partition){
		return ranges::count_if(d, [&](auto i){
			return !(partition< i);
		});
	});
	auto b = ranges::lower_bound(counts, (1+d.size())/2);
	return b-counts.begin()+low;
}


int main(){
	assert( median_uint({1, 1, 1}) == 1);
	assert( median_uint({10}) == 10);
	assert( median_uint({0, 1, 2, 3, 4}) == 2);
	assert( median_uint({0, 1, 1, 3, 4}) == 1);
	assert( median_uint({0, 1, 2, 3}) == 1);
	assert( median_uint({0, 1, 3, 4}) == 1);
	assert( median_uint({0, 0, 3, 4}) == 0);
	assert( median_uint({~0u}) == ~0u);
	assert( median_uint({~0u, 1, ~0u, 2, ~0u}) == ~0u);

    mt19937 engine;
	

	for(double n=10; n < 10'000'000; n*=1.2){
		
		auto start_time = steady_clock::now();

		for(int rep=0; rep < 10 ||steady_clock::now()-start_time< 1000ms ; rep++){
			uniform_int_distribution<> rng(0, n);

			vector<uint32_t> vi;
			for(int i=0; i < n; i++)
				vi.push_back(rng(engine));

				
			auto start = steady_clock::now();
			auto m1 = median_uint(vi);
			auto t1 = steady_clock::now() - start;

				
			start = steady_clock::now();
			auto m2 = median_uint2(vi);
			auto t2 = steady_clock::now() - start;

				
			start = steady_clock::now();
			auto nth = vi.begin() + (vi.size()-1)/2;
			nth_element(vi.begin(), nth, vi.end());
			auto mn = *nth;
			auto tn = steady_clock::now() - start;
			
			assert(m1 == mn);
			assert(m2 == mn);

			cout << n << " " << rep << " " << t1 << " " << t2 << " " << tn << endl;
		}



	}



}
