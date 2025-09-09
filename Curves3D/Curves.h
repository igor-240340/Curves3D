#pragma once

#include <numbers>
#include <cmath>

class Vec3f {
public:
	float x;
	float y;
	float z;

public:
	Vec3f() = default;
	Vec3f(float x, float y, float z) : x(x), y(y), z(z) {};

	Vec3f operator-(const Vec3f& b) const { return Vec3f{ x - b.x, y - b.y, z - b.z }; };

	float len() const { return std::sqrt(x * x + y * y + z * z); };
};

class Curve {
public:
	virtual Vec3f get_point(float t) const = 0;
	virtual Vec3f get_tan_vec(float t) const = 0;
	virtual ~Curve() = default;
	virtual std::string type_name() const = 0;
};

class Circle : public Curve {
public:
	explicit Circle(float r) : r(r) {
		if (r <= 0.0f)
			throw std::invalid_argument("Circle radius must be positive.");
	}

	Vec3f get_point(float t) const override {
		float x = std::cos(t) * r;
		float y = std::sin(t) * r;
		return Vec3f{ x, y, 0.0f };
	};

	Vec3f get_tan_vec(float t) const override {
		float x = -std::sin(t) * r;
		float y = std::cos(t) * r;
		return Vec3f{ x, y, 0.0f };
	};

	std::string type_name() const override { return "Circle"; };

public:
	float radius() const { return r; }
	static bool comparator(const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b) {
		return a->radius() < b->radius();
	}

private:
	const float r;
};

class Ellipse : public Curve {
public:
	// a - big radius.
	// b - small radius.
	Ellipse(float a, float b) : a(a), b(b) {
		if (a <= 0.0f || b <= 0.0f)
			throw std::invalid_argument("Both radii of ellipse must be positive.");
	}

	Vec3f get_point(float t) const override {
		float x = std::cos(t) * a;
		float y = std::sin(t) * b;
		return Vec3f{ x, y, 0.0f };
	};

	Vec3f get_tan_vec(float t) const override {
		float x = -std::sin(t) * a;
		float y = std::cos(t) * b;
		return Vec3f{ x, y, 0.0f };
	};

	std::string type_name() const override { return "Ellipse"; };

private:
	const float a;
	const float b;
};

class Helix : public Curve {
public:
	Helix(float r, float step) : r(r), step(step), z_slope(step / (2 * std::numbers::pi_v<float>)) {
		if (r <= 0.0f)
			throw std::invalid_argument("Helix radius must be positive.");

		if (step == 0.0f)
			throw std::invalid_argument("Helix mustn't be degenerate.");
	}

	Vec3f get_point(float t) const override {
		float x = std::cos(t) * r;
		float y = std::sin(t) * r;
		float z = z_slope * t;
		return Vec3f{ x, y, z };
	};

	Vec3f get_tan_vec(float t) const override {
		float x = -std::sin(t) * r;
		float y = std::cos(t) * r;
		return Vec3f{ x, y, z_slope };
	};

	std::string type_name() const override { return "Helix"; };

private:
	const float r;
	const float step;
	const float z_slope;
};
