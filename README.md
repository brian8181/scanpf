# roep (Re Organize Expression)

#### Usage

<pre><font color="#FFFFFF"><b>roep</b></font> [OPTIONS] <u style="text-decoration-style:single">INPUT_PATTERN</u> <u style="text-decoration-style:single">OUTPUT_PATTERN</u> <u style="text-decoration-style:single">[INPUT ...]</u>
</pre>

-todo options ...

#### Example

roep "\<a\>.\<b\> \<c\>" "\<c\> \<b\>.\<a\>" "A.B C" 
  
  output:
  
  "C B.A"
