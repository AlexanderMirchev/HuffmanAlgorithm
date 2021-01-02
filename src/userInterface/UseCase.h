#ifndef _USE_CASE_HH_
#define _USE_CASE_HH_

#include <iostream>

class UseCase
{
public:
    virtual ~UseCase() = default;
    virtual std::string operator()() const = 0;
};

class CompressionUseCase : public UseCase
{
private:
    std::string source;
    std::string destination;

public:
    CompressionUseCase() = delete;
    CompressionUseCase(const CompressionUseCase &) = delete;
    CompressionUseCase(const std::string &, const std::string &);
    ~CompressionUseCase() override = default;

    std::string operator()() const override;

private:
    std::string getPercentage(const double &) const;
};

class DecompressionUseCase : public UseCase
{
private:
    std::string source;
    std::string destination;

public:
    DecompressionUseCase() = delete;
    DecompressionUseCase(const DecompressionUseCase &) = delete;
    DecompressionUseCase(const std::string &, const std::string &);
    ~DecompressionUseCase() override = default;

    std::string operator()() const override;
};

#endif