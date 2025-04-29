package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.Config;

import java.util.regex.Pattern;

public class PatternTermTupleFilter extends AbstractTermTupleFilter {

    private Pattern pattern;

    /**
     * 构造函数
     *
     * @param input ：Filter的输入，类型为AbstractTermTupleStream
     */
    public PatternTermTupleFilter(AbstractTermTupleStream input) {
        super(input);
        this.pattern = Pattern.compile(Config.TERM_FILTER_PATTERN);
    }

    @Override
    public AbstractTermTuple next() {
        AbstractTermTuple termTuple = input.next();
        while (termTuple!=null && this.pattern != null && !(this.pattern.matcher(termTuple.term.getContent()).matches())){
            termTuple = input.next();
        }
        return termTuple;
    }
}
