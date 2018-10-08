double f(double x) {
    // Coding this
}
double simpson(double a, double b, double fl, double fr, double fm) {
    return (b - a) / 6 * (fl + 4 * fm + fr);
}
double integral(double l, double r, double fl, double fr, double fm, double EPS) {
    double m = (l + r) * 0.5;
    double flm = f((l + m) * 0.5), frm = f((m + r) * 0.5);
    double itg, itg_l, itg_r;
    itg = simpson(l, r, fl, fr, fm);
    itg_l = simpson(l, m, fl, fm, flm);
    itg_r = simpson(m, r, fm, fr, frm);
    if (fabs(itg_l + itg_r - itg) <= EPS)return itg;
    return integral(l, m, fl, fm, flm) + integral(m, r, fm, fr, frm);
}
double calc(double l, double r, double EPS) {
    return integral(l, r, f(l), f(r), f((l + r) * 0.5), EPS);
}