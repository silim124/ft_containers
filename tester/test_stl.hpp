/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stl.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:44:38 by silim             #+#    #+#             */
/*   Updated: 2022/05/28 15:48:38 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>

/*
 **=========================================================================
 **		 vector Test
 **=========================================================================
 */

static void printvector(const std::vector<std::string>& v) {
	for (size_t i = 0; i < v.size(); i++) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}

static void vector_test() {
	clock_t g_start = clock();

	std::vector<std::string> v1;
	v1.push_back("the");
	v1.push_back("frogurt");
	v1.push_back("is");
	v1.push_back("also");
	v1.push_back("cursed");
	std::cout << "v1: ";
	printvector(v1);

	std::vector<std::string> v2(v1.begin(), v1.end());
	std::cout << "v2: ";
	printvector(v2);

	std::vector<std::string> v3(v2);
	std::cout << "v3: ";
	printvector(v3);

	std::cout << "v3[1]: " << v3.at(1) << std::endl;
	std::cout << "v3[2]: " << v3[2] << std::endl;
	std::cout << "v3 front: " << v3.front() << std::endl;
	std::cout << "v3 back: " << v3.back() << std::endl;

	std::vector<std::string>::iterator it = v3.begin();
	for (; it < v3.end(); it++) {
		std::cout << "it: " << *it << " ";
	}
	std::cout << std::endl;

	std::vector<std::string>::reverse_iterator rvrIt = v3.rbegin();
	for (; rvrIt < v3.rend(); rvrIt++) {
		std::cout << "rvrIt: " << *rvrIt << " ";
	}
	std::cout << std::endl;

	std::cout << "v3 empty: " << (v3.empty() ? "true" : "false") << std::endl;
	std::cout << "v3 size: " << v3.size() << std::endl;
	std::cout << "v3 max_size: " << v3.max_size() << std::endl;
	std::cout << "v3 capacity: " << v3.capacity() << std::endl;

	std::cout << "v3 clear\n";
	v3.clear();
	std::cout << "v3 size: " << v3.size() << std::endl;
	std::cout << "v3 insert (from v2)\n";
	v3.insert(v3.begin(), v2.begin(), v2.end());
	std::cout << "v3 size: " << v3.size() << std::endl;
	std::cout << "v3: ";
	printvector(v3);

	std::cout << "erase first\n";
	v3.erase(v3.begin() + 1);
	std::cout << "v3: ";
	printvector(v3);

	v3.push_back("foo");
	v3.push_back("bar");
	v3.push_back("kek");
	std::cout << "v3: ";
	printvector(v3);

	v3.pop_back();
	std::cout << "v3: ";
	printvector(v3);

	v3.resize(4);
	std::cout << "v3: ";
	printvector(v3);

	v3.assign(2, "newWord");
	std::cout << "v3: ";
	printvector(v3);

	v3.swap(v2);
	std::cout << "v3: ";
	printvector(v3);

	std::cout << "v3 == v2: " << (v3 == v2 ? "true" : "false") << std::endl;
	std::cout << "v3 < v2: " << (v3 < v2 ? "true" : "false") << std::endl;
	std::cout << "v3 >= v2: " << (v3 >= v2 ? "true" : "false") << std::endl;

	std::vector<int> v4;
	for (int i = 0; i < 300000; i++) {
		v4.push_back(i);
	}

	clock_t g_end = clock();
	printf("Execution time (ms): %.2fms\n",
				 (double)(g_end - g_start) / CLOCKS_PER_SEC * 1000);
}

/*
 **=========================================================================
 **		 stack Test
 **=========================================================================
 */

static void stack_test() {
	clock_t g_start = clock();

	std::stack<int> st;
	for (int i = 0; i < 100000; i++) {
		st.push(i * 3);
	}
	std::cout << "Top element (st): " << st.top() << std::endl;
	std::cout << "stack size (st): " << (st.empty() ? "true" : "false")
						<< std::endl;

	std::stack<int> st2(st);
	std::cout << "Top element (st2): " << st2.top() << std::endl;
	std::cout << "stack size (st2): " << (st2.empty() ? "true" : "false")
						<< std::endl;
	std::cout << "stack empty (st2): " << (st2.empty() ? "true" : "false")
						<< std::endl;

	st2.push(99);
	st2.push(42);
	std::cout << "Top element (st2): " << st2.top() << std::endl;
	std::cout << "stack size (st2): " << (st2.empty() ? "true" : "false")
						<< std::endl;

	std::stack<int> st3 = st2;
	std::cout << "st2 == st3: " << (st2 == st3 ? "true" : "false") << std::endl;

	st3.pop();
	st3.pop();
	st3.pop();
	st3.pop();
	st3.pop();
	std::cout << "Top element (st3): " << st2.top() << std::endl;
	std::cout << "st2 == st3: " << (st2 == st3 ? "true" : "false") << std::endl;
	std::cout << "st2 != st3: " << (st2 != st3 ? "true" : "false") << std::endl;
	std::cout << "st2 < st3: " << (st2 < st3 ? "true" : "false") << std::endl;
	std::cout << "st2 >= st3: " << (st2 >= st3 ? "true" : "false") << std::endl;

	int count = 0;
	while (!st3.empty()) {
		count++;
		st3.pop();
	}
	std::cout << "Count of pop operations (st3): " << count << std::endl;
	std::cout << "stack empty (st3): " << (st3.empty() ? "true" : "false")
						<< std::endl;

	clock_t g_end = clock();
	printf("Execution time (ms): %.2fms\n",
				 (double)(g_end - g_start) / CLOCKS_PER_SEC * 1000);
}

/*
 **=========================================================================
 **		 map Test
 **=========================================================================
 */

static void printmap(const std::map<std::string, int>& m) {
	std::cout << '{';
	std::map<std::string, int>::const_iterator b = m.begin();
	std::map<std::string, int>::const_iterator e = m.end();
	while (b != e) {
		std::cout << b->first << ':' << b->second << ' ';
		b++;
	}
	std::cout << "}\n";
}

static void map_test() {
	clock_t g_start = clock();

	std::map<std::string, int> mp1;
	mp1["something"] = 21;
	mp1["anything"] = 42;
	mp1["that thing"] = 121;
	mp1["whatever"] = 555;
	std::cout << "mp1: ";
	printmap(mp1);

	std::map<std::string, int> mp2(mp1.find("anything"), mp1.end());
	std::cout << "mp2: ";
	printmap(mp2);

	std::map<std::string, int> mp3(mp1);
	std::cout << "mp3: ";
	printmap(mp3);

	std::cout << "mp3[anything] with []: " << mp3["anything"] << std::endl;
	std::cout << "mp3[non_existing] with []: " << mp3["non_existing"]
	<< std::endl;
	printmap(mp3);

	std::map<std::string, int>::reverse_iterator rvrIt = mp3.rbegin();
	std::cout << '{';
	for (; rvrIt != mp3.rend(); rvrIt++) {
		std::cout << rvrIt->first << ':' << rvrIt->second << ' ';
	}
	std::cout << "}\n";

	std::cout << "mp3 empty: " << (mp3.empty() ? "true" : "false") << std::endl;
	std::cout << "mp3 size: " << mp3.size() << std::endl;

	std::cout << "mp3 clear\n";
	mp3.clear();
	std::cout << "mp3 size: " << mp3.size() << std::endl;
	std::cout << "mp3 insert (from mp2)\n";
	mp3.insert(mp2.begin(), mp2.end());
	std::cout << "mp3 size: " << mp3.size() << std::endl;
	std::cout << "mp3: ";
	printmap(mp3);

	std::cout << "erase 'that_thing'\n";
	mp3.erase(mp3.find("that thing"));
	std::cout << "erase 'non_existing'\n";
	mp3.erase("non_existing");
	std::cout << "mp3: ";
	printmap(mp3);

	mp3.swap(mp2);
	std::cout << "mp3: ";
	printmap(mp3);

	std::cout << "mp3 == mp2: " << (mp3 == mp2 ? "true" : "false") << std::endl;
	std::cout << "mp3 < mp2: " << (mp3 < mp2 ? "true" : "false") << std::endl;
	std::cout << "mp3 >= mp2: " << (mp3 >= mp2 ? "true" : "false") << std::endl;

	std::map<int, int> mp4;
	for (int i = 0, j = 100; i < 300000; i++, j++) {
		mp4.insert(std::make_pair(i * 2, j));
	}
	std::cout << "count 41: " << mp4.count(41) << std::endl;
	std::cout << "count 50: " << mp4.count(50) << std::endl;
	std::cout << "count 300005: " << mp4.count(300005) << std::endl;
	std::cout << "find 26: " << mp4.find(26)->first << std::endl;
	std::cout << "lower bound 127: " << mp4.lower_bound(127)->first << std::endl;
	std::cout << "upper bound 244: " << mp4.upper_bound(244)->first << std::endl;

	clock_t g_end = clock();
	printf("Execution time (ms): %.2fms\n",
				 (double)(g_end - g_start) / CLOCKS_PER_SEC * 1000);
}

/*
 **=========================================================================
 **		 Launch Tests
 **=========================================================================
 */

int test_stl() {
	std::cout << "(test stl)" << std::endl;
	std::cout << "\n***** VECTOR TEST *****\n" << std::endl;
	vector_test();
	std::cout << std::endl;

	std::cout << "\n***** STACK TEST *****\n" << std::endl;
	stack_test();
	std::cout << std::endl;

	std::cout << "\n***** MAP TEST *****\n" << std::endl;
	map_test();
	std::cout << std::endl;

	return 0;
}
