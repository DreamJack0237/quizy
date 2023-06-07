import React from 'react'
import {
  Link,
  Routes,
  Route,
  useNavigate,
} from 'react-router-dom';

const Create = () => {

  const navigate = useNavigate();

  return (
    <div className=''>

      <div className='center1 center'>
        <h2>Cree votre Qcm</h2>
      </div>


      <div className='MainCreate'>

        <div className='CreateQuestion flex'>

          <input type="text" name='Question' />
          <button className='Btn'>Add Question</button>


          <input type="text" label='entrer votre matier' />

          <button className='Btn' >Ajouter Matiere</button>

        </div>

        <div className='CreateAnswer flex'>
          <label htmlFor="Answer">Inscrivez vos reponses ici</label>
          <input type="text" name=" Answer" ></input>
          <input type="text"></input>
          <input type="text"></input>
          <input type="text"></input>
          <input type="text"></input>

        </div>

      </div>

      <div className='center margint'>
        <button className='Btn exite' onClick={() => navigate(-1)}>Go back / Exite</button>
      </div>


    </div>
  )
}

export default Create