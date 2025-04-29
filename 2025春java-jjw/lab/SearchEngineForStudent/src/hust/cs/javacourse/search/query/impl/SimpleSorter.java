package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.Sort;

import java.util.List;
import java.util.Map;

public class SimpleSorter implements Sort {
    @Override
    public void sort(List<AbstractHit> hits) {
        hits.sort((a,b)->{
            return (int)(-score(a)+score(b));
        });
    }

    @Override
    public double score(AbstractHit hit) {
        double score = 0;
        for(Map.Entry<AbstractTerm, AbstractPosting> entry: hit.getTermPostingMapping().entrySet()){
            score +=entry.getValue().getFreq();
        }
        return score;
    }
}
