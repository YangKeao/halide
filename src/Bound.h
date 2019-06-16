//
// Created by yangkeao on 6/16/19.
//

#ifndef HALIDE_BOUND_H
#define HALIDE_BOUND_H


namespace Halide {
    template<typename T>
    class Bound {
      private:
        T start;
        T end;
      public:
        Bound<T>(T start, T end): start(start), end(end) {};
        T getStart() const {
            return start;
        }

        T getEnd() const {
            return end;
        }
    };
}


#endif //HALIDE_BOUND_H
