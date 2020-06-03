#pragma once

template <typename Enum>
class EnumConverter
{
public:
    template<typename ConvValueType>
    void convert(ConvValueType value, std::initializer_list<Enum> list)
    {
        isError_ = true;
        for (Enum item : list)
        {
            if (static_cast<ConvValueType>(item) == value)
            {
                result_ = item;
                isError_ = false;
                break;
            }
        }
    };

    bool error() const { return isError_; }
    Enum result() const { return result_; }
private:
    bool isError_;
    Enum result_;
};