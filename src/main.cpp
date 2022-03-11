#include <remover.hpp>

#include <memory>

int main(int argc, char* argv[])
{
	std::unique_ptr<Remover> r(new Remover);
	return r->run(argc, argv);
}