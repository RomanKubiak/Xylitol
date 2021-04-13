//
// Created by atom on 03.04.2021.
//

#ifndef XYLITOL_UTILS_H
#define XYLITOL_UTILS_H

template <class T>
inline const T& Min (const T& a, const T& b)
{
    return b < a ? b : a;
}

template <class T>
inline const T& Max (const T& a, const T& b)
{
    return a < b ? b : a;
}

template <class T>
inline T Abs (const T& value)
{
    return (value >= (T)0) ? value : -value;
}

template <class T>
inline T Sign (const T& value)
{
    return (value == (T)0) ? 0 : ((value >= (T)0) ? 1 : -1);
}

template <class T>
inline T Bound (T minval, T maxval, T x)
{
    if (x < minval)
        return minval;
    else if (x > maxval)
        return maxval;
    return x;
}

template <class T>
void Swap (T& t1, T& t2)
{
    T tmp = t1;
    t1 = t2;
    t2 = tmp;
}

template <class T>
bool IsApproximateEqual (T t1, T t2, T epsilon)
{
    if (t1 == t2)
        return true;
    T diff = t1 - t2;
    if (diff < 0.0)
        diff = -diff;
    if (diff < epsilon)
        return true;
    return false;
}

template <class T>
inline T ToNormalized (const T& value, const int32_t numSteps)
{
    return value / T (numSteps);
}

template <class T>
inline int32_t FromNormalized (const T& norm, const int32_t numSteps)
{
    return Min<int32_t> (numSteps, int32_t (norm * (numSteps + 1)));
}

#endif //XYLITOL_UTILS_H
