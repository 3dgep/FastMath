# C++ Templates

<tldr>
    <p>C++ templates are used to describe a family of classes (<emphasis>class templates</emphasis>), a family of functions (<emphasis>function templates</emphasis>), or a family of variables (<emphasis>variable templates</emphasis>).</p>
</tldr>

C++ template programming is not a new concept. 
Templates have been around a long time, and there are plenty of articles and resources on the internet that describe C++ template programming.
In this article, I do not attempt to describe C++ template programming beyond what is required to build the C++ template math library in this series.
If you are interested in learning about _variadic templates_,  _type traits_, _SFINAE_, or _Concepts_ in greater detail, 
then I recommend you read ["C++ templates: The Complete Guide, 2nd Edition" by David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor][tmplbook].
Or, if you'd prefer a more condensed article on C++ templates, I recommend you check out [C++ Template Programming](https://www.3dgep.com/beginning-cpp-template-programming) on 3dgep.com.

I will limit this article to the following topics:

1. Function Templates
2. Class Templates
3. Variable Templates
4. Template Specialization
5. Partial Specialization
6. Variadic Templates

I think those topics should keep us busy enough and provide a good foundation that is required to create the C++ template math library for use in games.

<seealso>
    <category ref="reading">
        <a href="http://www.tmplbook.com/">C++ Templates - The Complete Guide, 2nd Ed.</a>
    </category>
    <category ref="external">
        <a href="https://www.3dgep.com/beginning-cpp-template-programming">C++ Template Programming</a>
    </category>
</seealso>


[tmplbook]: http://www.tmplbook.com/