#pragma once

#include <map>
#include <string>

class Function{
    public:
        virtual void evaluate(double*, double*, int) = 0;
        virtual double derivative(double*, int) = 0;
        virtual char const* get_name() = 0;
};

class Activation: public Function{};

class Loss: public Function{
    public:
        virtual void set_target(double* target) = 0;
};

class Sigmoid: public Activation{
    public:
        void evaluate(double* x, double* ans, int size);
        double derivative(double* x, int element);
        char const* get_name();
};

class LessSquare: public Loss{
    double * y;

    public:
        void set_target(double* target);
        void evaluate(double* y_hat, double* ans, int size);
        double derivative(double* y_hat, int element);
        char const* get_name();
};

class Function_creator{
    std::map<std::string, Activation* (Function_creator::*)()> activations_map;
    std::map<std::string, Loss* (Function_creator::*)()> loss_map;

    public:
        Function_creator();
        Activation* create_activation(std::string);
        Loss* create_loss(std::string);
        template<class T> Activation* create_activation_function();
        template<class T> Loss* create_loss_function();
};
