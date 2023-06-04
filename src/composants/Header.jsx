import React from 'react'
import { FiMenu } from 'react-icons/fi';
import Qcm from './Qcm';


const Header = () => {

  return (
    <div className='mainnav'>
      <button className='nav1 navs Btn'>
        Qcm
      </button>
      <button className='nav2 navs Btn1 Btn'>
        Create
      </button>
      <div className="Fimenu">
        <FiMenu />
      </div>
      <Qcm />
    </div>
  )
}

export default Header