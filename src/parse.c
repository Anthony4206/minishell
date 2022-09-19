/**
 *
	<list>          ::=     '(' <command line> ')'  '||'    <list>
                        |   '(' <command line> ')'  '&&'    <list>
                        |   '(' <command line> ')'  '<'     <list>
                        |   '(' <command line> ')'  '>'     <list>
                        |   '(' <command line> ')'  '>>'    <list>
                        |   '(' <command line> ')'  '<<'    <list>
                        |   '(' <command line> ')'  '|'     <list>
                        |   '(' <command line> ')'
                        |   <command line>
    
    <command line>	::= 	<job> '||' <command line>
						| 	<job> '&&' <command line>
							<job>

	<job>			::=		<command>   '|'     <job>
						|	<command>   '||'    <job>
						|	<command>   '&&'    <job>’
						|	<command>

	<command>		::=		<simple command> '<' <filename>
						|	<simple command> '>' <filename>
						|	<simple command> '>>' <filename>
						|	<simple command> '<<' <EOF>
						|	<simple command>

	<simple command>::=		<pathname> <token list>

	<token list>	::=		<token> <token list>
						|	(EMPTY)
 *
**/