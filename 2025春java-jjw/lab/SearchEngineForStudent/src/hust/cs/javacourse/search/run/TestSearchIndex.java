package hust.cs.javacourse.search.run;

import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.AbstractIndexSearcher;
import hust.cs.javacourse.search.query.Sort;
import hust.cs.javacourse.search.query.impl.IndexSearcher;
import hust.cs.javacourse.search.query.impl.SimpleSorter;
import hust.cs.javacourse.search.util.Config;

import javax.swing.plaf.nimbus.AbstractRegionPainter;

/**
 * 测试搜索
 */
public class TestSearchIndex {
    /**
     *  搜索程序入口
     * @param args ：命令行参数
     */
    public static void main(String[] args){

        Sort simpleSorter = new SimpleSorter();
        String indexFile = Config.INDEX_DIR + "index.dat";
        AbstractIndexSearcher searcher = new IndexSearcher();
        searcher.open(indexFile);

//        System.out.println("-------Single word query-------");
//        AbstractHit[] hits = searcher.search(new Term("luxembourg"), simpleSorter);
//        if (hits == null || hits.length==0){
//            System.out.println("No hits found");
//            return;
//        }
//        for(AbstractHit hit : hits){
//            System.out.println(hit);
//        }

//        System.out.println("-------Double word query OR-------");
//        AbstractHit[] hits2 = searcher.search(new Term("wales"), new Term("health"),simpleSorter, AbstractIndexSearcher.LogicalCombination.OR);
//        if (hits2 == null || hits2.length == 0){
//            System.out.println("No hits found");
//            return;
//        }
//        for(AbstractHit hit : hits2){
//            System.out.println(hit);
//        }

        System.out.println("-------Phrase query-------");
        AbstractHit[] hits2 = searcher.search(new Term("watching"), new Term("Television"),simpleSorter, AbstractIndexSearcher.LogicalCombination.ADJACENT);
        if (hits2 == null || hits2.length == 0){
            System.out.println("No hits found");
            return;
        }
        for(AbstractHit hit : hits2){
            System.out.println(hit);
        }
    }
}
