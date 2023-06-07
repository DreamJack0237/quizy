/* eslint-disable no-undef */
import React from 'react'
import {
  Link,
  Routes,
  Route,
  useNavigate,
} from 'react-router-dom';

const Create = () => {

  const navigate = useNavigate();

  const onaddquestion = () => {

    let questions = []
    questions.push(rep1.value)
    questions.push(rep2.value)
    questions.push(rep3.value)
    questions.push(rep4.value)

    sql(`insert into quiz (n) values ("${mat.value}") ;`)
    let m = sql(`select * from quiz where n="${mat.value}";`)
    console.log(m)
    console.log(`insert into question (quizid,lib) values (${m.id},"${question.value}") ;`)
    sql(`insert into question (quizid,lib) values (${m[0].id},"${question.value}") ;`)
    let qu = sql(`SELECT COUNT(*) as count FROM question;`)
    console.log(qu)
    for (let q of questions) {
      if (q !== '') {
        sql(`insert into answer (questionid,lib) values (${parseInt(parseInt(qu[0].count))},"${q}"); `)
      }
    }
  }
  return (
    <div className=''>

      <div className='center1 center'>
        <h2>Cree votre Qcm</h2>
      </div>


      <div className='MainCreate'>

        <div className='CreateQuestion flex'>

          <input type="text" id='mat' label='entrer votre matier' placeholder='Matiere' />

          <input type="text" name='Question' id='question' placeholder='Question' />
          <button className='Btn' onClick={onaddquestion}>Add Question</button>




        </div>

        <div className='CreateAnswer flex'>
          <label htmlFor="Answer">Inscrivez vos reponses ici</label>
          <input type="text" id='rep1' placeholder='Choix1'></input>
          <input type="text" id='rep2' placeholder='Choix2'></input>
          <input type="text" id='rep3' placeholder='Choix3'></input>
          <input type="text" id='rep4' placeholder='Choix4'></input>

        </div>

      </div>

      <div className='center margint'>
        <button className='Btn exite' onClick={() => navigate(-1)}>Go back / Exite</button>
      </div>


    </div>
  )
}

export default Create