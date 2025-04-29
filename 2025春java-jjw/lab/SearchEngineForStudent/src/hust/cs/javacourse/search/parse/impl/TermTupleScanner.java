package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.index.impl.TermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleScanner;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StringSplitter;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class TermTupleScanner extends AbstractTermTupleScanner {
    private int curPos = -1;
    private int prePos = 0;
    private List<String> curWordsList;
    private final StringSplitter splitter = new StringSplitter();
    {
        splitter.setSplitRegex(Config.STRING_SPLITTER_REGEX);
    }

    public TermTupleScanner() {
        super();
    }

    public TermTupleScanner(BufferedReader input) {
        super(input);
    }

    @Override
    public AbstractTermTuple next() {
        if (input == null) return null;

        curPos++;

        while (curWordsList == null || curWordsList.isEmpty() || curPos >= curWordsList.size()) {
            prePos += (curWordsList != null) ? curWordsList.size() : 0;
            String newLine = null;
            try {
                newLine = input.readLine();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

            if (newLine == null) {
                return null;
            }

            curWordsList = splitter.splitByRegex(newLine);
            curPos = 0;
        }
        return new TermTuple(curWordsList.get(curPos).toLowerCase(), prePos + curPos);
    }

    public static void main(String[] args) {
        BufferedReader br;
        try {
            br = new BufferedReader(new FileReader(Config.DOC_DIR + "功能测试数据集/1.txt"));
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }

        TermTupleScanner termTupleScanner = new TermTupleScanner(br);

        while (true) {
            AbstractTermTuple termTuple = termTupleScanner.next();
            if (termTuple == null) break;
            System.out.println(termTuple);
        }
    }
}
