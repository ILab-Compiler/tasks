/**
 * @file	task/iv_tests.h
 * 
 * @author	Sergey Ivanychev, DCAM MIPT
 * @brief	Some added unit tests and dump print is located here
 */


DList<double> d_list;
UTEST_CHECK( utest_p, d_list.empty() == true);
d_list.push_front(1.0);



d_list.push_front(2.0);
d_list.push_back (-2.0);
d_list.push_back (-1.0);
UTEST_CHECK(utest_p, d_list.last() -> prev() -> val() == -2.0);
UTEST_CHECK(utest_p, d_list.empty() == false);
UTEST_CHECK(utest_p, d_list.size() == 4);
d_list.insert(d_list.last(), 42.0);
UTEST_CHECK(utest_p, d_list.last() -> prev() -> val() == 42.0);

d_list.dump(stdout);


