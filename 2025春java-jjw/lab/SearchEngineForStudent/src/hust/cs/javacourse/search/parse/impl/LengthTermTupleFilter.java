package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.Config;

public class LengthTermTupleFilter extends AbstractTermTupleFilter {

    private int maxLength;
    private int minLength;

    /**
     * 构造函数
     *
     * @param input ：Filter的输入，类型为AbstractTermTupleStream
     */
    public LengthTermTupleFilter(AbstractTermTupleStream input) {
        super(input);
        this.minLength = Config.TERM_FILTER_MINLENGTH;
        this.maxLength = Config.TERM_FILTER_MAXLENGTH;
    }


    @Override
    public AbstractTermTuple next() {
        AbstractTermTuple termTuple = input.next();
        while (termTuple != null && (termTuple.term.getContent().length() > maxLength || termTuple.term.getContent().length() < minLength)) {
            termTuple = input.next();
        }
        return termTuple;
    }
}
