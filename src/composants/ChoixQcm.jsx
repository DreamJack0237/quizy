/* eslint-disable no-undef */
import React, { useEffect, useState } from 'react'
import Header from './Header'
import { Link } from "react-router-dom";

const ChoixQcm = () => {

    const [quizs, setquizs] = useState([])
    // eslint-disable-next-line no-undef
    useEffect(() => {
        console.log(sql("select * from quiz;"))
        setquizs(sql("select * from quiz;"))
    }, [])
    console.log()
    return (
        <div className='flex'>
            <Header />
            <div>
                {
                    quizs.map((quiz) => {
                        return (
                            <div className='Question '>
                                <Link to="/Qcm" className='choix'>
                                    {quiz.name}
                                </Link>
                            </div>
                        )
                    })
                }

            </div>


        </div>
    )

}

export default ChoixQcm