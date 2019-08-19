#include <bits/stdc++.h>
#define MULTIPLICATIVE_EPSILON (1 + 1e-14)

using namespace std;

struct Point  {
    
    double x, y;
	
	Point operator- (const Point &p) const{
        return {x - p.x, y - p.y};
    }

    double distance(const Point &p){
        return hypot(x - p.x, y - p.y);
    }

    double operator* (const Point &p)const{
        return x * p.y - y * p.x;
    }
	
};


struct Circle {
	Point c;
    double r;  
	
    bool contains(const Point &p) {
        return c.distance(p) <= r * MULTIPLICATIVE_EPSILON;
    }
	
	bool contains(const vector<Point> &ps) {
        for(const Point &p : ps) {
            if(!contains(p))
                return false;
        }
        return true;
    }
	
};

Circle INVALID(){
    return {{0, 0}, -1};
}


static default_random_engine randGen((random_device())());


Circle makeDiameter(const Point &a, const Point &b) {
	Point c{(a.x + b.x) / 2, (a.y + b.y) / 2};
	return Circle{c, max(c.distance(a), c.distance(b))};
}

Circle makeCircumcircle(const Point &a, const Point &b, const Point &c) {
	// Mathematical algorithm from Wikipedia: Circumscribed circle
	double ox = (min(min(a.x, b.x), c.x) + max(min(a.x, b.x), c.x)) / 2;
	double oy = (min(min(a.y, b.y), c.y) + max(min(a.y, b.y), c.y)) / 2;
	double ax = a.x - ox,  ay = a.y - oy;
	double bx = b.x - ox,  by = b.y - oy;
	double cx = c.x - ox,  cy = c.y - oy;
	double d = (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by)) * 2;
	if (d == 0)
		return INVALID();
	double x = ((ax*ax + ay*ay) * (by - cy) + (bx*bx + by*by) * (cy - ay) + (cx*cx + cy*cy) * (ay - by)) / d;
	double y = ((ax*ax + ay*ay) * (cx - bx) + (bx*bx + by*by) * (ax - cx) + (cx*cx + cy*cy) * (bx - ax)) / d;
	Point p{ox + x, oy + y};
	double r = max(max(p.distance(a), p.distance(b)), p.distance(c));
	return Circle{p, r};
}


// Two boundary points known
static Circle makeSmallestEnclosingCircleTwoPoints(const vector<Point> &points, size_t end, const Point &p, const Point &q) {
	Circle circ = makeDiameter(p, q);
	Circle left  = INVALID();
	Circle right = INVALID();
	
	// For each point not in the two-point circle
	Point pq = q - p;
	for (size_t i = 0; i < end; i++) {
		const Point &r = points.at(i);
		if (circ.contains(r))
			continue;
		
		// Form a circumcircle and classify it on left or right side
		double cross = pq * (r - p);
		Circle c = makeCircumcircle(p, q, r);
		if (c.r < 0)
			continue;
		else if (cross > 0 && (left.r < 0 || pq * (c.c - p) > pq * (left.c - p)))
			left = c;
		else if (cross < 0 && (right.r < 0 || pq * (c.c - p) < pq * (right.c - p)))
			right = c;
	}
	
	// Select which circle to return
	if (left.r < 0 && right.r < 0)
		return circ;
	else if (left.r < 0)
		return right;
	else if (right.r < 0)
		return left;
	else
		return left.r <= right.r ? left : right;
}

// One boundary point known
static Circle makeSmallestEnclosingCircleOnePoint(const vector<Point> &points, size_t end, const Point &p) {
	Circle c{p, 0};
	for (size_t i = 0; i < end; i++) {
		const Point &q = points.at(i);
		if (!c.contains(q)) {
			if (c.r == 0)
				c = makeDiameter(p, q);
			else
				c = makeSmallestEnclosingCircleTwoPoints(points, i + 1, p, q);
		}
	}
	return c;
}


// Initially: No boundary points known
Circle makeSmallestEnclosingCircle(const vector<Point> &points) {
	// Clone list to preserve the caller's data, randomize order
	vector<Point> shuffled = points;
	shuffle(shuffled.begin(), shuffled.end(), randGen);
	
	// Progressively add points to circle or recompute circle
	Circle c = INVALID();
	for (size_t i = 0; i < shuffled.size(); i++) {
		const Point &p = shuffled.at(i);
		if (c.r < 0 || !c.contains(p))
			c = makeSmallestEnclosingCircleOnePoint(shuffled, i + 1, p);
	}
	return c;
}

int main(){
    int n;
    scanf("%d", &n);
    vector <Point> points;
    for(int i = 0; i < n; i++){
        double a, b;
        scanf(" %lf %lf", &a, &b);
        points.push_back({a, b});
    }
    Circle resp = makeSmallestEnclosingCircle(points);
    double aux = 0;
    for(int i = 0; i < n; i++){
        aux = max(aux, max(abs(resp.c.x - points[i].x), abs(resp.c.y - points[i].y)));
    }
    printf("%.17f %.17f %.17f\n", resp.c.x, resp.c.y, aux);
    return 0;
}
