# Inline Calculator
Solves arithmetic expressions written by user in a console window in a single line. More functions can be added later.
- Interprets specified single characters as mathematical operators and constants
<br />Operators
<br />`+` *plus*
<br />`-` *minus*
<br />`*` *times*
<br />`/` *divide by*
<br />`^` *to the power of*
<br />`r` *square root of*
<br />Constants
<br />`x` *ans*
<br />`p` *π*
<br />`e` *e*
<br />Other
<br />`q` *quit program*
- Respects conventional evaluation order (multiply/divide before add/subtract)
<br />`2+2*2` gives **6**
- Supports parentheses
<br />`(2+2)*2` gives **8**
- Recursively solves nested expressions in parentheses
<br />`9+(5*(3-1))` gives **19**
---
#### Final Example
`(15-(7+3))*2^3+r64` gives **48**
