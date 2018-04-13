#pragma once

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "Parser.h"
#include "location.hh"

namespace Grammar{

	class Scanner : public yyFlexLexer{
	public:
        Scanner() = default;

		Scanner(std::istream *in) : yyFlexLexer(in)
		{
		};
		virtual ~Scanner() {
		};

//		//get rid of override virtual function warning
//		using FlexLexer::yylex;

        Parser::symbol_type Lex();
//		virtual
//		Parser::token_type yylex( Parser::semantic_type* lval,
//				   Parser::location_type* location );
		// YY_DECL defined in mc_lexer.l
		// Method body created by flex in mc_lexer.yy.cc


	private:
		/* yyval ptr */
		Parser::semantic_type *yylval = nullptr;
        Parser::location_type loc;
	};

}