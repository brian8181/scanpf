# scanpf (Re Organize Expression)
## hello

#### Usage

<pre><font color="#FFFFFF"><b>scanpf</b></font> [OPTIONS] <u style="text-decoration-style:single">INPUT_PATTERN</u> <u style="text-decoration-style:single">OUTPUT_PATTERN</u> <u style="text-decoration-style:single">[INPUT ...]</u>
</pre>

-todo options ...

#### Example

scanpf "\<a\>.\<b\> \<c\>" "\<c\> \<b\>.\<a\>" "A.B C" 
  
  output:
  
  "C B.A"
