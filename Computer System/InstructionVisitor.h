#pragma once

namespace ownfos
{
	class Move;
	class Jump;
	class Load;
	class Store;
	class Add;

	class InstructionVisitor
	{
	public:
		virtual void Visit(const Move* move) = 0;
		virtual void Visit(const Jump* move) = 0;
		virtual void Visit(const Load* move) = 0;
		virtual void Visit(const Store* move) = 0;
		virtual void Visit(const Add* move) = 0;
	};
}