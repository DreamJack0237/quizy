/* eslint-disable no-undef */
import React, { useEffect, useState } from 'react'
import Header from './Header'
import Time from './Time'
import { useParams } from 'react-router-dom'

const Qcm = () => {

    const { id } = useParams()
    const [qandr, setqandr] = useState([])
    const getquestions = () => {
        let r = []
        let quizquestions = sql(`select * from question where quizid=${id}`)
        for (let q of quizquestions) {
            let reps = sql(`select * from answer where questionid=${parseInt(q.id)}`)
            r.push({
                question: q,
                reps: reps
            })
        }

        console.log(r)

        setqandr(r)

    }
    useEffect(() => {
        getquestions()
    }, [])
    return (
        <div className='flex'>
            <Header />
            <div className='justify'>

                <div className='flex col'>

                    {
                        qandr.map((q, i) => {

                            return (
                                <>
                                    <div className='Question'>
                                        <p className='Questionn_umber'>{i + 1}.</p>
                                        <h1 className='Question_text'>
                                            {q.question.lib}
                                        </h1>
                                    </div>

                                    <div className='main_options'>
                                        {
                                            q.reps.map((rep) => {
                                                return (
                                                    <div className='options'>
                                                        <label className="switch">
                                                            <input type="checkbox" />
                                                            <span className="slider"><p>D.</p></span>
                                                        </label>
                                                        <div>
                                                            <p>
                                                                {rep.lib}
                                                            </p>
                                                        </div>
                                                    </div>
                                                )
                                            })
                                        }


                                    </div>
                                </>

                            )
                        })


                    }

                    <div className='Asubmit flex'>
                        <button className='submitbtn'>
                            Submit
                        </button>
                    </div>
                </div>



                <div className='flex spbt pad10 control'>

                    <Time />

                    <button className="NextPage">
                        Next page &#65125;
                    </button>

                </div>


            </div>

        </div>
    )
}

export default Qcm