//
// Created by yangkeao on 5/27/19.
//

#ifndef HALIDE_FUNC_H
#define HALIDE_FUNC_H

#include <vector>
#include <memory>
#include "Var.h"
#include "Expr.h"
#include "Buffer.h"
#include "Util.h"

namespace Halide {
    class Func: public Expr {
        bool definition = false;
        std::string name = Internal::make_entity_name("func");
        Expr* impls;
        std::unique_ptr<std::vector<Var>> args;
      public:
        Func() = default;

        Func& operator()(std::vector<Var>);

        template <typename... Args>
        Func& operator()(Args&&... args);

        template <typename T>
        Func &operator+=(T expr) {
            this->impls = (Expr*)&(*(this->impls) + expr);
            return *this;
        }

        template <typename T>
        Func &operator-=(T expr) {
            this->impls = (Expr*)&(*(this->impls) - expr);
            return *this;
        }

        template <typename T>
        Func &operator*=(T expr) {
            this->impls = (Expr*)&(*(this->impls) * expr);
            return *this;
        }

        template <typename T>
        Func &operator/=(T expr) {
            this->impls = (Expr*)&(*(this->impls) / expr);
            return *this;
        }

        Func& operator=(Expr&);

        bool isDefinition() {return definition;}

        Buffer realize(int width, int height, int offsetX, int offsetY);

        void* codegen(CompileCtx&) override;
    };

    template<typename... Args>
    Func& Func::operator()(Args &&... args) {
        std::vector<Var> collected_args{std::forward<Args>(args)...};
        return this->operator()(collected_args);
    }
}


#endif //HALIDE_FUNC_H
