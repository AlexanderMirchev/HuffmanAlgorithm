#ifndef _USE_CASE_HH_
#define _USE_CASE_HH_

#include <string>

class UseCase
{
public:
    virtual ~UseCase() = default;
    virtual std::string operator()() const = 0;
};

class CompressionUseCase : public UseCase
{
protected:
    std::string source;
    std::string destination;

public:
    CompressionUseCase() = delete;
    CompressionUseCase(const CompressionUseCase &) = delete;
    CompressionUseCase(const std::string &, const std::string &);
    ~CompressionUseCase() = default;

    std::string operator()() const override;

protected:
    std::string getPercentage(const double &) const;
};

class CompressionDbgUseCase : public CompressionUseCase
{
public:
    CompressionDbgUseCase(const CompressionDbgUseCase &) = delete;
    CompressionDbgUseCase(const std::string &, const std::string &);
    CompressionDbgUseCase() = default;

    std::string operator()() const override;
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
    ~DecompressionUseCase() = default;

    std::string operator()() const override;
};

#endif
