#include <iostream>
#include <string>
#include <functional>

std::function<void()> g_callback;


class Foo : public std::enable_shared_from_this<Foo>
{
public:
    Foo()
    {
        std::cout << "Foo created\n";

        m_str = "Hello, World!";
    }

    ~Foo()
    {
        std::cout << "Foo destroyed\n";
    }

    void Register()
    {
        auto self = shared_from_this();

        std::cout << "1. " << self.use_count() << std::endl;

        g_callback = [this, self]()
            {
                std::cout << "2. " << self.use_count() << std::endl;
                DoSomething();
            };
    }

    void DoSomething()
    {
        std::cout << "Doing something\n";

        std::cout << m_str << "\n";
    }


private:

    std::string m_str;
};

int main()
{
    {
        auto f = std::make_shared<Foo>();
        std::cout << "Before. " << f.use_count() << std::endl;
        f->Register();

        std::cout << "After. " << f.use_count() << std::endl;

    }

    std::cout << "Calling callback...\n";


    g_callback();

    return 0;
}
