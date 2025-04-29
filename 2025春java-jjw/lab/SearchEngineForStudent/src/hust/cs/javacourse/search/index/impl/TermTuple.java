package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;

import java.util.Objects;

public class TermTuple extends AbstractTermTuple {
    public TermTuple(){
        super();
    }

    public TermTuple(String word, int curPos) {
        this.term = new Term(word);
        this.curPos = curPos;
    }
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj.getClass() != TermTuple.class) return false;
        TermTuple termTuple = (TermTuple) obj;
        return Objects.equals(this.term, termTuple.term) && this.curPos == termTuple.curPos;
    }

    @Override
    public String toString() {
        return "TermTuple( term = " + term + ", curPos = " + curPos + ")";
    }
}
