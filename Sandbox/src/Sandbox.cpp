#include <Poly.h>
#include <Poly/Core/EntryPoint.h>

class Sandbox : public Poly::Application
{
public:
	Sandbox(const Poly::ApplicationSpecification& specification)
		: Poly::Application(specification)
	{

	}

	~Sandbox()
	{

	}
};

Poly::Application* Poly::CreateApplication(Poly::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.CommandLineArgs = args;

	return new Sandbox(spec);
}