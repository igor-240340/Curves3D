#pragma once

#include <cassert>
#include <stdexcept>
#include <iostream>

#include "Curves.h"

constexpr float epsilon = 1e-06;

class TestCircle {
public:
	static void run() {
		test_circle_zero_r();
		test_circle_neg_r();
		test_circle_get_point();
		test_circle_get_tan_vec();
	}

private:
	static void test_circle_zero_r() {
		std::cout << "test_circle_zero_r: ";
		try {
			Circle c{ 0.0f };
		}
		catch (const std::exception& e) {
			assert(true);
			std::cout << "OK\n";
			return;
		}
		assert(false);
	}

	static void test_circle_neg_r() {
		std::cout << "test_circle_neg_r: ";
		try {
			Circle c{ -1.0f };
		}
		catch (const std::exception& e) {
			assert(true);
			std::cout << "OK\n";
			return;
		}
		assert(false);
	}

	static void test_circle_get_point() {
		std::cout << "test_circle_get_point: ";
		Circle c{ 1.123f };
		float t = 5.432f;

		Vec3f expected_point{ 0.74016052309554333844f, -0.8445658056367968159f, 0.0f };
		Vec3f actual_point = c.get_point(t);
		assert((actual_point - expected_point).len() <= epsilon);
		std::cout << "OK\n";
	}

	static void test_circle_get_tan_vec() {
		std::cout << "test_circle_get_tan_vec: ";
		Circle c{ 1.123f };
		float t = 5.432f;

		Vec3f expected_tan_vec{ 0.8445658056367968159f, 0.74016052309554333844f, 0.0f };
		Vec3f actual_tan_vec = c.get_tan_vec(t);
		assert((actual_tan_vec - expected_tan_vec).len() <= epsilon);
		std::cout << "OK\n";
	}
};

class TestEllipse {
public:
	static void run() {
		test_ellipse_zero_a();
		test_ellipse_zero_b();
		test_ellipse_neg_a();
		test_ellipse_neg_b();
		test_ellipse_get_point();
		test_ellipse_get_tan_vec();
	}

private:
	static void test_ellipse_zero_a() {
		std::cout << "test_ellipse_zero_a: ";
		try {
			Ellipse e{ 0.0f, 1.0f };
		}
		catch (const std::exception& e) {
			assert(true);
			std::cout << "OK\n";
			return;
		}
		assert(false);
	}

	static void test_ellipse_zero_b() {
		std::cout << "test_ellipse_zero_b: ";
		try {
			Ellipse e{ 1.0f, 0.0f };
		}
		catch (const std::exception& e) {
			assert(true);
			std::cout << "OK\n";
			return;
		}
		assert(false);
	}

	static void test_ellipse_neg_a() {
		std::cout << "test_ellipse_neg_a: ";
		try {
			Ellipse e{ -1.0f, 1.0f };
		}
		catch (const std::exception& e) {
			assert(true);
			std::cout << "OK\n";
			return;
		}
		assert(false);
	}

	static void test_ellipse_neg_b() {
		std::cout << "test_ellipse_neg_b: ";
		try {
			Ellipse e{ 1.0f, -1.0f };
		}
		catch (const std::exception& e) {
			assert(true);
			std::cout << "OK\n";
			return;
		}
		assert(false);
	}

	static void test_ellipse_get_point() {
		std::cout << "test_ellipse_get_point: ";
		Ellipse e{ 1.123f, 2.87754f };
		float t = 5.432f;

		Vec3f expected_point{ 0.74016052309554333844f, -2.1640889477756975153f, 0.0f };
		Vec3f actual_point = e.get_point(t);
		assert((actual_point - expected_point).len() <= epsilon);
		std::cout << "OK\n";
	}

	static void test_ellipse_get_tan_vec() {
		std::cout << "test_ellipse_get_point: ";
		Ellipse e{ 1.123f,  2.87754f };
		float t = 5.432f;

		Vec3f expected_tan_vec{ 0.8445658056367968159f, 1.8965641243351289208f, 0.0f };
		Vec3f actual_tan_vec = e.get_tan_vec(t);
		assert((actual_tan_vec - expected_tan_vec).len() <= epsilon);
		std::cout << "OK\n";
	}
};

class TestHelix {
public:
	static void run() {
		test_helix_zero_r();
		test_helix_neg_r();
		test_helix_zero_step();
		test_helix_get_point();
		test_helix_get_tan_vec();
	}

private:
	static void test_helix_zero_r() {
		std::cout << "test_helix_zero_r: ";
		try {
			Helix h{ 0.0f, 1.0f };
		}
		catch (const std::exception& e) {
			assert(true);
			std::cout << "OK\n";
			return;
		}
		assert(false);
	}

	static void test_helix_neg_r() {
		std::cout << "test_helix_neg_r: ";
		try {
			Helix c{ -1.0f, 1.0f };
		}
		catch (const std::exception& e) {
			assert(true);
			std::cout << "OK\n";
			return;
		}
		assert(false);
	}

	static void test_helix_zero_step() {
		std::cout << "test_helix_zero_step: ";
		try {
			Helix c{ 1.0f, 0.0f };
		}
		catch (const std::exception& e) {
			assert(true);
			std::cout << "OK\n";
			return;
		}
		assert(false);
	}

	static void test_helix_get_point() {
		std::cout << "test_helix_get_point: ";
		Helix c{ 1.123f, 0.634f };
		float t = 10.432f;

		Vec3f expected_point{ -0.59991910100066798824f, -0.94932927493812720891f, 1.0526329682561694585f };
		Vec3f actual_point = c.get_point(t);
		assert((actual_point - expected_point).len() <= epsilon);
		std::cout << "OK\n";
	}

	static void test_helix_get_tan_vec() {
		std::cout << "test_helix_get_tan_vec: ";
		Helix c{ 1.123f, 0.634f };
		float t = 10.432f;

		Vec3f expected_tan_vec{ 0.94932927493812720891f, -0.59991910100066798824f, 0.10090423392026164288f };
		Vec3f actual_tan_vec = c.get_tan_vec(t);
		assert((actual_tan_vec - expected_tan_vec).len() <= epsilon);
		std::cout << "OK\n";
	}
};

class Test {
public:
	static void run_all() {
		TestCircle::run();
		std::cout << '\n';

		TestEllipse::run();
		std::cout << '\n';

		TestHelix::run();
		std::cout << '\n';
	}
};