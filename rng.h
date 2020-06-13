namespace rng {
#include <random>

inline auto &global_urng() {
  static std::mt19937 u{};
  return u;
}

inline unsigned int randomize() {
  static std::random_device rd{};
  unsigned int sed = rd();
  global_urng().seed(sed);
  return sed;
}

inline unsigned int randomize(unsigned int sed) {
  global_urng().seed(sed);
  return sed;
}

inline int irn(int from, int thru) {
  static std::uniform_int_distribution<> d{};
  using parm_t = decltype(d)::param_type;
  return d(global_urng(), parm_t{from, thru});
}

inline double urn(double from = 0.0, double upto = 1.0) {
  static std::uniform_real_distribution<> d{};
  using param_t = decltype(d)::param_type;
  return d(global_urng(), param_t{from, upto});
}
}; // namespace rng