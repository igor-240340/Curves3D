#include <iostream>
#include <memory>
#include <random>
#include <format>
#include <algorithm>
#include <numeric>

#include "Curves.h"

#ifdef _DEBUG
#include "Test.h"
#endif

std::vector<std::shared_ptr<Curve>> populate_curves(int curves_count);
void print_points_and_tans(const std::vector<std::shared_ptr<Curve>>& curves);
std::vector<std::shared_ptr<Circle>> populate_circles(const std::vector<std::shared_ptr<Curve>>& curves);
void sort_circles(std::vector<std::shared_ptr<Circle>>& circles);
float comp_total_radius(const std::vector<std::shared_ptr<Circle>>& circles);

int main() {
#ifdef _DEBUG
	Test::run_all();
#endif

	try {
		std::vector<std::shared_ptr<Curve>> curves = populate_curves(10);
		print_points_and_tans(curves);
		std::vector<std::shared_ptr<Circle>> circles = populate_circles(curves);
		sort_circles(circles);
		float total_radius = comp_total_radius(circles);
		std::cout << "\nTotal sum of radii: " << total_radius << '\n';

		return 0;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
		return 1;
	}
}

std::vector<std::shared_ptr<Curve>> populate_curves(int curves_count) {
	enum class CurveType {
		Circle,
		Ellipse,
		Helix
	};

	std::random_device rd;
	std::mt19937 gen{ rd() };
	std::uniform_int_distribution<int> curve_type_dist(0, 2);
	//std::uniform_real_distribution<float> float_dist(std::numeric_limits<float>::denorm_min(), std::numeric_limits<float>::max());
	std::uniform_real_distribution<float> float_dist(std::numeric_limits<float>::denorm_min(), 1000.0f);

	std::vector<std::shared_ptr<Curve>> curves;
	curves.reserve(curves_count);
	for (int i = 0; i < curves_count; ++i) {
		CurveType type = static_cast<CurveType>(curve_type_dist(gen));
		switch (type) {
		case CurveType::Circle: {
			float r = float_dist(gen);
			curves.emplace_back(std::make_shared<Circle>(r));
			break;
		}

		case CurveType::Ellipse: {
			// NOTE: We consider ellipse with a = b not as degenerate but as a special case.
			float a = float_dist(gen);
			float b = float_dist(gen);
			curves.emplace_back(std::make_shared<Ellipse>(a, b));
			break;
		}

		case CurveType::Helix: {
			float r = float_dist(gen);
			float step = float_dist(gen);
			curves.emplace_back(std::make_shared<Helix>(r, step));
			break;
		}
		}
	}

	return curves;
}

void print_points_and_tans(const std::vector<std::shared_ptr<Curve>>& curves) {
	constexpr float t = std::numbers::pi_v<float> / 4;
	for (const std::shared_ptr<Curve>& c : curves) {
		Vec3f point = c->get_point(t);
		Vec3f tan_vec = c->get_tan_vec(t);
		std::cout << std::format("{}\npoint({}) => ({},{},{})\n", c->type_name(), t, point.x, point.y, point.z);
		std::cout << std::format("tan({}) => ({},{},{})\n\n", t, tan_vec.x, tan_vec.y, tan_vec.z);
	}
}

std::vector<std::shared_ptr<Circle>> populate_circles(const std::vector<std::shared_ptr<Curve>>& curves) {
	std::vector<std::shared_ptr<Circle>> circles;
	circles.reserve(curves.size());
	for (const std::shared_ptr<Curve>& curve : curves) {
		if (std::shared_ptr<Circle> circle = std::dynamic_pointer_cast<Circle>(curve); circle != nullptr) {
			circles.push_back(circle);
		}
	}

	return circles;
}

void sort_circles(std::vector<std::shared_ptr<Circle>>& circles) {
	std::sort(circles.begin(), circles.end(), Circle::comparator);
	for (const std::shared_ptr<Circle>& c : circles)
		std::cout << std::format("radius={}\n", c->radius());
}

float comp_total_radius(const std::vector<std::shared_ptr<Circle>>& circles) {
	return std::accumulate(
		circles.begin(), circles.end(), 0.0f,
		[](float acc, const std::shared_ptr<Circle>& c) { return acc + c->radius(); }
	);
}
