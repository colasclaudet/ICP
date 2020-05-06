#ifndef STATISTICS_H
#define STATISTICS_H


class Statistics
{
public:
    Statistics();
    void init();
    int nb_iterations;
    int nb_point;
    double deviation_min;
    double deviation_ave;
    double deviation_max;
    double ecart_type;
    double under_tol;
private:
    bool is_init = false;
};

#endif // STATISTICS_H
