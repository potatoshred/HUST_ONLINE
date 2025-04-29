package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.index.impl.TermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StopWords;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class StopWordTermTupleFilter extends AbstractTermTupleFilter {

    private List<String> stopWords;

    public StopWordTermTupleFilter(AbstractTermTupleStream input){
        super(input);
        this.stopWords = Arrays.asList(StopWords.STOP_WORDS);
    }

    /**
     * 构造函数
     *
     * @param input ：Filter的输入，类型为AbstractTermTupleStream
     */
    public StopWordTermTupleFilter(AbstractTermTupleStream input, List<String> stopWords) {
        super(input);
        this.stopWords = stopWords;
    }

    @Override
    public AbstractTermTuple next() {
        AbstractTermTuple termTuple = input.next();
        while (termTuple!=null && this.stopWords != null && this.stopWords.contains(termTuple.term.getContent())){
            termTuple = input.next();
        }
        return termTuple;
    }

    public static void main(String[] args) {
        BufferedReader br;
        try {
            br = new BufferedReader(new FileReader(Config.DOC_DIR + "功能测试数据集/1.txt"));
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }

        TermTupleScanner termTupleScanner = new TermTupleScanner(br);
        List<String> stopWords = Arrays.asList(StopWords.STOP_WORDS);
        StopWordTermTupleFilter stopWordTermTupleFilter = new StopWordTermTupleFilter(termTupleScanner, stopWords);

        while (true){
            AbstractTermTuple termTuple = stopWordTermTupleFilter.next();
            if (termTuple == null) break;
            System.out.println(termTuple);
        }

    }
}
