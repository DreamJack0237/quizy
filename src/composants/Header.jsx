import React from 'react'
import { FiMenu } from 'react-icons/fi';
import { Outlet, Link } from "react-router-dom";
import '../App.css';


const Header = () => {
    return (
        <div className='main1'>
            <div className='mainnav'>
                
                <div className="Fimenu">
                    <FiMenu />
                </div>

                <Link className='navs Btn' to="/Qcm">
                    <button className='nav1'>
                        Qcm
                    </button>
                </Link>

                <Link className='navs Btn' to="/Create">
                    <button className='nav2 navs Btn1 '>
                        Create
                    </button>
                </Link>


            </div>

            <div className='secondarynav'>
                code space
            </div>
        </div>

    )
}

export default Header