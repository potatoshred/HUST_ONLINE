package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractDocument;
import hust.cs.javacourse.search.index.AbstractDocumentBuilder;
import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.parse.impl.LengthTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.PatternTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.StopWordTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.TermTupleScanner;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.FileUtil;
import hust.cs.javacourse.search.util.StopWords;

import java.io.*;
import java.util.Arrays;
import java.util.List;

public class DocumentBuilder extends AbstractDocumentBuilder {
    @Override
    public AbstractDocument build(int docId, String docPath, AbstractTermTupleStream termTupleStream) {
        Document doc = new Document(docId, docPath);
        AbstractTermTuple tuple;
        while (true){
            tuple = termTupleStream.next();
            if (tuple == null){
                break;
            }
            doc.addTuple(tuple);
        }

        return doc;
    }

    @Override
    public AbstractDocument build(int docId, String docPath, File file) {
        Document doc = new Document(docId, docPath);
        BufferedReader br;
        try {
            br = new BufferedReader(new FileReader(file));
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }

        TermTupleScanner termTupleScanner = new TermTupleScanner(br);
        AbstractTermTupleFilter filter = new StopWordTermTupleFilter(new PatternTermTupleFilter(new LengthTermTupleFilter(termTupleScanner)));

        AbstractTermTuple termTuple;
        while (true) {
            termTuple = filter.next();
            if (termTuple == null) break;
            doc.addTuple(termTuple);
        }

        return doc;
    }

    public static void main(String[] args) {
        String filePath = Config.DOC_DIR + "功能测试数据集/2.txt";
        File f = new File(filePath);
        AbstractDocument doc = new DocumentBuilder().build(1, filePath, f);
        System.out.println(doc);

        BufferedReader br;
        try {
            br = new BufferedReader(new FileReader(Config.DOC_DIR + "功能测试数据集/2.txt"));
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
        TermTupleScanner termTupleScanner = new TermTupleScanner(br);
        List<String> stopWords = Arrays.asList(StopWords.STOP_WORDS);
        StopWordTermTupleFilter stopWordTermTupleFilter = new StopWordTermTupleFilter(new PatternTermTupleFilter(new LengthTermTupleFilter(termTupleScanner)));
        AbstractDocument doc2 = new DocumentBuilder().build(2, filePath, stopWordTermTupleFilter);
        System.out.println(doc2);

    }
}
